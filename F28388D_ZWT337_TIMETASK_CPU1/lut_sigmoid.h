/*
 * lut_sigmoid.h
 *
 *  Created on: Apr 26, 2024
 *      Author: User
 */

#ifndef LUT_SIGMOID_H_
#define LUT_SIGMOID_H_

#define COSINE_TYPE    0
#define EXP_TYPE       1
#define TABLE_TYPE     COSINE_TYPE

#if (TABLE_TYPE == COSINE_TYPE)
#define STEP_SCALE    1.0f
#else
#define STEP_SCALE    0.5f
#endif

// Constants for the lookup table
#define LOOKUP_SIZE 65
#define MIN_X -6.0f
#define MAX_X 6.0f
#define STEP ((LOOKUP_SIZE - 1) / (MAX_X - MIN_X))

// Lookup table for the sigmoid function as a constant array
extern const float32_t sigmoidLookup[LOOKUP_SIZE];

static inline float32_t getSigmoidPoint(float32_t x /*must be a positive of PU*/) {
    float32_t f32Input = (csatUpu(x)-0.5f)*2.0f *10.0f;

    if (f32Input <= MIN_X) return sigmoidLookup[0];
    if (f32Input >= MAX_X) return sigmoidLookup[LOOKUP_SIZE - 1];

    float32_t f32Index = (f32Input - MIN_X) * STEP;
    int32_t s32Index = (int32_t)f32Index;
    if (s32Index >= LOOKUP_SIZE - 1) {
        return sigmoidLookup[LOOKUP_SIZE - 1];
    }
    float32_t f32Factor = f32Index - s32Index;
    return sigmoidLookup[s32Index] * (1 - f32Factor) + sigmoidLookup[s32Index + 1] * f32Factor;
}

typedef volatile struct {
    float32_t f32Xperiod; //usec
    float32_t f32Xsample; //usec
    float32_t f32Xtrans;
    float32_t f32Xstep;
    float32_t f32Xindex;
    float32_t f32Xtarget;
    float32_t f32Yoffset;
    float32_t f32Ytarget;
    float32_t f32Ydelta;
    float32_t f32Youtput;
}ST_SIGMOID;

typedef ST_SIGMOID * HAL_SIGMOID;

#define DEFAULT_SIGMOID (ST_SIGMOID) { \
    .f32Xperiod = 1000.0, \
    .f32Xsample = 10.0, \
    .f32Xtrans = 0.0f, \
    .f32Xstep = 0.0f, \
    .f32Xindex = 0.0f, \
    .f32Xtarget = 0.0f, \
    .f32Yoffset = 0.0f, \
    .f32Ytarget = 0.0f, \
    .f32Ydelta = 0.0f, \
    .f32Youtput = 0.0f \
}


static inline float32_t setSigmoidStep(float32_t f32Target, HAL_SIGMOID v)
{
    v->f32Ytarget = csatUpu(f32Target);
    v->f32Yoffset = v->f32Youtput;
    v->f32Ydelta = v->f32Ytarget - v->f32Yoffset;

    if(0.0f < v->f32Ydelta) {
        v->f32Xindex = 0.0f;
        v->f32Xtrans = v->f32Ydelta * v->f32Xperiod;
        v->f32Xstep = v->f32Xsample / v->f32Xtrans * 0.5f;

    }
    else if(0.0f > v->f32Ydelta) {
        v->f32Xindex = 0.0f;
        v->f32Xtrans = -1.0f * v->f32Ydelta * v->f32Xperiod;
        v->f32Xstep = v->f32Xsample / v->f32Xtrans * 0.5f;
    }
    else { // if(v->f32Yoffset == v->f32Ytarget)
        v->f32Xindex = 0.0f;
        v->f32Xstep = 0.0f;
    }

    return v->f32Ytarget;
}

static inline float32_t runSigmoidRamp(HAL_SIGMOID v)
{
    if(v->f32Xindex < v->f32Xtrans) {
        v->f32Youtput = v->f32Yoffset + v->f32Ydelta * getSigmoidPoint(v->f32Xindex);
        v->f32Xindex += v->f32Xstep;
    }
    else {
        v->f32Youtput = v->f32Yoffset = v->f32Ytarget;
    }


    return v->f32Youtput;
}

static inline void rstSigmoidRamp(float32_t f32Data, HAL_SIGMOID v)
{
     v->f32Youtput = v->f32Yoffset = v->f32Ytarget = f32Data;
}


#endif /* LUT_SIGMOID_H_ */
