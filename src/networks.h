#pragma once
#ifndef NETWORKS_H
#    define NETWORKS_H
#    include <stdbool.h>
#    include "scrappie_matrix.h"
#    include "scrappie_structures.h"

enum raw_model_type {
    SCRAPPIE_MODEL_RAW=0,
    SCRAPPIE_MODEL_RGR,
    SCRAPPIE_MODEL_RGRGR_R9_4,
    SCRAPPIE_MODEL_RGRGR_R9_5,
    SCRAPPIE_MODEL_RGRGR_R10,
    SCRAPPIE_MODEL_RNNRF_R9_4,
    SCRAPPIE_MODEL_RGRGR_RESGRU,
    SCRAPPIE_MODEL_RGRGR_RESLSTM,
    SCRAPPIE_MODEL_INVALID};

enum squiggle_model_type {
    SCRAPPIE_SQUIGGLE_MODEL_R9_4,
    SCRAPPIE_SQUIGGLE_MODEL_R10,
    SCRAPPIE_SQUIGGLE_MODEL_INVALID};

typedef scrappie_matrix (*posterior_function_ptr)(const raw_table, float, float, float, bool);

enum raw_model_type get_raw_model(const char * modelstr);
const char * raw_model_string(const enum raw_model_type model);
int get_raw_model_stride(const enum raw_model_type model);
posterior_function_ptr get_posterior_function(const enum raw_model_type model);

typedef scrappie_matrix (*squiggle_function_ptr)(int const * sequence, size_t, bool);

enum squiggle_model_type get_squiggle_model(const char * squigmodelstr);
const char * squiggle_model_string(const enum squiggle_model_type squiggle_model);
squiggle_function_ptr get_squiggle_function(const enum squiggle_model_type squiggle_model);

//  Events posterior.  Other models via factory function
scrappie_matrix nanonet_posterior(const event_table events, float min_prob,
		                  float tempW, float tempb, bool return_log);

//  Raw posterior -- for preference, use get_posterior_function
scrappie_matrix nanonet_raw_posterior(const raw_table signal, float min_prob,
		                      float tempW, float tempb, bool return_log);
scrappie_matrix nanonet_rgr_posterior(const raw_table signal, float min_prob,
		                      float tempW, float tempb, bool return_log);
scrappie_matrix nanonet_rgrgr_r94_posterior(const raw_table signal, float min_prob,
		                            float tempW, float tempb, bool return_log);
scrappie_matrix nanonet_rgrgr_r95_posterior(const raw_table signal, float min_prob,
		                            float tempW, float tempb, bool return_log);
scrappie_matrix nanonet_rgrgr_r10_posterior(const raw_table signal, float min_prob,
		                             float tempW, float tempb, bool return_log);
scrappie_matrix nanonet_rnnrf_r94_transitions(const raw_table signal, float min_prob,
		                              float tempW, float tempb, bool return_log);
scrappie_matrix nanonet_rgrgr_resgru_posterior(const raw_table signal, float min_prob,
		                               float tempW, float tempb, bool return_log);
scrappie_matrix nanonet_rgrgr_reslstm_posterior(const raw_table signal, float min_prob,
		                                float tempW, float tempb, bool return_log);

//  Squiggle functions
scrappie_matrix squiggle_r94(int const * sequence, size_t n, bool transform_units);
scrappie_matrix squiggle_r10(int const * sequence, size_t n, bool transform_units);

#endif    /* NETWORKS_H */
