/* Include files */

#include <stddef.h>
#include "blas.h"
#include "component_model_sfun.h"
#include "c2_component_model.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "component_model_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[36] = { "R", "gamma", "gamma2", "Hu",
  "yita", "yita_mech0", "yita_mech1", "yita_mech2", "J1", "J2", "J3", "V", "Vcc",
  "beita", "mcc", "nargin", "nargout", "Thc", "Tlc", "Tcc", "mfan", "mhc", "mf",
  "mht", "mlt", "Pcc", "N1", "N2", "Tlt", "Tht", "Td", "Tfin", "dotTcc", "dotN1",
  "dotN2", "dotPcc" };

static const char * c2_b_debug_family_names[10] = { "cp1", "cp2", "cp3", "cp4",
  "cp5", "cp6", "nargin", "nargout", "T", "cp_a" };

static const char * c2_c_debug_family_names[10] = { "cp1", "cp2", "cp3", "cp4",
  "cp5", "cp6", "nargin", "nargout", "T", "cp_hg" };

/* Function Declarations */
static void initialize_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance);
static void initialize_params_c2_component_model
  (SFc2_component_modelInstanceStruct *chartInstance);
static void enable_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance);
static void disable_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_component_model
  (SFc2_component_modelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_component_model
  (SFc2_component_modelInstanceStruct *chartInstance);
static void set_sim_state_c2_component_model(SFc2_component_modelInstanceStruct *
  chartInstance, const mxArray *c2_st);
static void finalize_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance);
static void sf_gateway_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance);
static void c2_chartstep_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance);
static void initSimStructsc2_component_model(SFc2_component_modelInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_dotPcc, const char_T *c2_identifier);
static real_T c2_b_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u);
static real_T c2_cp_air(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_T);
static void c2_eml_scalar_eg(SFc2_component_modelInstanceStruct *chartInstance);
static real_T c2_mpower(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_a);
static real_T c2_b_mpower(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_a);
static real_T c2_c_mpower(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_a);
static real_T c2_cp_hotgas(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_T);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_c_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_d_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_component_model, const char_T
  *c2_identifier);
static uint8_T c2_e_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_component_modelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_component_model = 0U;
}

static void initialize_params_c2_component_model
  (SFc2_component_modelInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_component_model
  (SFc2_component_modelInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_component_model
  (SFc2_component_modelInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T c2_c_hoistedGlobal;
  real_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real_T c2_d_hoistedGlobal;
  real_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  uint8_T c2_e_hoistedGlobal;
  uint8_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  real_T *c2_dotN1;
  real_T *c2_dotN2;
  real_T *c2_dotPcc;
  real_T *c2_dotTcc;
  c2_dotPcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_dotN2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_dotN1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_dotTcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(5, 1), false);
  c2_hoistedGlobal = *c2_dotN1;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = *c2_dotN2;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_c_hoistedGlobal = *c2_dotPcc;
  c2_c_u = c2_c_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_d_hoistedGlobal = *c2_dotTcc;
  c2_d_u = c2_d_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_e_hoistedGlobal = chartInstance->c2_is_active_c2_component_model;
  c2_e_u = c2_e_hoistedGlobal;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 4, c2_f_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_component_model(SFc2_component_modelInstanceStruct *
  chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T *c2_dotN1;
  real_T *c2_dotN2;
  real_T *c2_dotPcc;
  real_T *c2_dotTcc;
  c2_dotPcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_dotN2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_dotN1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_dotTcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  *c2_dotN1 = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u,
    0)), "dotN1");
  *c2_dotN2 = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u,
    1)), "dotN2");
  *c2_dotPcc = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u,
    2)), "dotPcc");
  *c2_dotTcc = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u,
    3)), "dotTcc");
  chartInstance->c2_is_active_c2_component_model = c2_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 4)),
     "is_active_c2_component_model");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_component_model(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance)
{
  real_T *c2_Thc;
  real_T *c2_Tlc;
  real_T *c2_dotTcc;
  real_T *c2_Tcc;
  real_T *c2_mfan;
  real_T *c2_mhc;
  real_T *c2_mf;
  real_T *c2_mht;
  real_T *c2_mlt;
  real_T *c2_Pcc;
  real_T *c2_N1;
  real_T *c2_N2;
  real_T *c2_Tlt;
  real_T *c2_Tht;
  real_T *c2_Td;
  real_T *c2_dotN1;
  real_T *c2_dotN2;
  real_T *c2_dotPcc;
  real_T *c2_Tfin;
  c2_Tfin = (real_T *)ssGetInputPortSignal(chartInstance->S, 14);
  c2_dotPcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_dotN2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_dotN1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_Td = (real_T *)ssGetInputPortSignal(chartInstance->S, 13);
  c2_Tht = (real_T *)ssGetInputPortSignal(chartInstance->S, 12);
  c2_Tlt = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
  c2_N2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 10);
  c2_N1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
  c2_Pcc = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
  c2_mlt = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c2_mht = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c2_mf = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c2_mhc = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c2_mfan = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c2_Tcc = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_dotTcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_Tlc = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_Thc = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c2_Thc, 0U);
  _SFD_DATA_RANGE_CHECK(*c2_Tlc, 1U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_component_model(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_component_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*c2_dotTcc, 2U);
  _SFD_DATA_RANGE_CHECK(*c2_Tcc, 3U);
  _SFD_DATA_RANGE_CHECK(*c2_mfan, 4U);
  _SFD_DATA_RANGE_CHECK(*c2_mhc, 5U);
  _SFD_DATA_RANGE_CHECK(*c2_mf, 6U);
  _SFD_DATA_RANGE_CHECK(*c2_mht, 7U);
  _SFD_DATA_RANGE_CHECK(*c2_mlt, 8U);
  _SFD_DATA_RANGE_CHECK(*c2_Pcc, 9U);
  _SFD_DATA_RANGE_CHECK(*c2_N1, 10U);
  _SFD_DATA_RANGE_CHECK(*c2_N2, 11U);
  _SFD_DATA_RANGE_CHECK(*c2_Tlt, 12U);
  _SFD_DATA_RANGE_CHECK(*c2_Tht, 13U);
  _SFD_DATA_RANGE_CHECK(*c2_Td, 14U);
  _SFD_DATA_RANGE_CHECK(*c2_dotN1, 15U);
  _SFD_DATA_RANGE_CHECK(*c2_dotN2, 16U);
  _SFD_DATA_RANGE_CHECK(*c2_dotPcc, 17U);
  _SFD_DATA_RANGE_CHECK(*c2_Tfin, 18U);
}

static void c2_chartstep_c2_component_model(SFc2_component_modelInstanceStruct
  *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  real_T c2_d_hoistedGlobal;
  real_T c2_e_hoistedGlobal;
  real_T c2_f_hoistedGlobal;
  real_T c2_g_hoistedGlobal;
  real_T c2_h_hoistedGlobal;
  real_T c2_i_hoistedGlobal;
  real_T c2_j_hoistedGlobal;
  real_T c2_k_hoistedGlobal;
  real_T c2_l_hoistedGlobal;
  real_T c2_m_hoistedGlobal;
  real_T c2_n_hoistedGlobal;
  real_T c2_o_hoistedGlobal;
  real_T c2_Thc;
  real_T c2_Tlc;
  real_T c2_Tcc;
  real_T c2_mfan;
  real_T c2_mhc;
  real_T c2_mf;
  real_T c2_mht;
  real_T c2_mlt;
  real_T c2_Pcc;
  real_T c2_N1;
  real_T c2_N2;
  real_T c2_Tlt;
  real_T c2_Tht;
  real_T c2_Td;
  real_T c2_Tfin;
  uint32_T c2_debug_family_var_map[36];
  real_T c2_R;
  real_T c2_gamma;
  real_T c2_gamma2;
  real_T c2_Hu;
  real_T c2_yita;
  real_T c2_yita_mech0;
  real_T c2_yita_mech1;
  real_T c2_yita_mech2;
  real_T c2_J1;
  real_T c2_J2;
  real_T c2_J3;
  real_T c2_V;
  real_T c2_Vcc;
  real_T c2_beita;
  real_T c2_mcc;
  real_T c2_nargin = 15.0;
  real_T c2_nargout = 4.0;
  real_T c2_dotTcc;
  real_T c2_dotN1;
  real_T c2_dotN2;
  real_T c2_dotPcc;
  real_T c2_A;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_y;
  real_T c2_b_A;
  real_T c2_B;
  real_T c2_d_x;
  real_T c2_b_y;
  real_T c2_e_x;
  real_T c2_c_y;
  real_T c2_f_x;
  real_T c2_d_y;
  real_T c2_e_y;
  real_T c2_c_A;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_f_y;
  real_T c2_d_A;
  real_T c2_b_B;
  real_T c2_j_x;
  real_T c2_g_y;
  real_T c2_k_x;
  real_T c2_h_y;
  real_T c2_l_x;
  real_T c2_i_y;
  real_T c2_e_A;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_j_y;
  real_T c2_f_A;
  real_T c2_c_B;
  real_T c2_p_x;
  real_T c2_k_y;
  real_T c2_q_x;
  real_T c2_l_y;
  real_T c2_r_x;
  real_T c2_m_y;
  real_T c2_n_y;
  real_T c2_g_A;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_h_A;
  real_T c2_v_x;
  real_T c2_w_x;
  real_T c2_x_x;
  real_T c2_o_y;
  real_T c2_i_A;
  real_T c2_d_B;
  real_T c2_y_x;
  real_T c2_p_y;
  real_T c2_ab_x;
  real_T c2_q_y;
  real_T c2_bb_x;
  real_T c2_r_y;
  real_T c2_s_y;
  real_T c2_j_A;
  real_T c2_cb_x;
  real_T c2_db_x;
  real_T c2_eb_x;
  real_T c2_k_A;
  real_T c2_e_B;
  real_T c2_fb_x;
  real_T c2_t_y;
  real_T c2_gb_x;
  real_T c2_u_y;
  real_T c2_hb_x;
  real_T c2_v_y;
  real_T c2_w_y;
  real_T c2_l_A;
  real_T c2_ib_x;
  real_T c2_jb_x;
  real_T c2_kb_x;
  real_T c2_x_y;
  real_T *c2_b_dotPcc;
  real_T *c2_b_dotN2;
  real_T *c2_b_dotN1;
  real_T *c2_b_dotTcc;
  real_T *c2_b_Tfin;
  real_T *c2_b_Td;
  real_T *c2_b_Tht;
  real_T *c2_b_Tlt;
  real_T *c2_b_N2;
  real_T *c2_b_N1;
  real_T *c2_b_Pcc;
  real_T *c2_b_mlt;
  real_T *c2_b_mht;
  real_T *c2_b_mf;
  real_T *c2_b_mhc;
  real_T *c2_b_mfan;
  real_T *c2_b_Tcc;
  real_T *c2_b_Tlc;
  real_T *c2_b_Thc;
  c2_b_Tfin = (real_T *)ssGetInputPortSignal(chartInstance->S, 14);
  c2_b_dotPcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_b_dotN2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_b_dotN1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_b_Td = (real_T *)ssGetInputPortSignal(chartInstance->S, 13);
  c2_b_Tht = (real_T *)ssGetInputPortSignal(chartInstance->S, 12);
  c2_b_Tlt = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
  c2_b_N2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 10);
  c2_b_N1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
  c2_b_Pcc = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
  c2_b_mlt = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c2_b_mht = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c2_b_mf = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c2_b_mhc = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c2_b_mfan = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_Tcc = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_b_dotTcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_Tlc = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_Thc = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_Thc;
  c2_b_hoistedGlobal = *c2_b_Tlc;
  c2_c_hoistedGlobal = *c2_b_Tcc;
  c2_d_hoistedGlobal = *c2_b_mfan;
  c2_e_hoistedGlobal = *c2_b_mhc;
  c2_f_hoistedGlobal = *c2_b_mf;
  c2_g_hoistedGlobal = *c2_b_mht;
  c2_h_hoistedGlobal = *c2_b_mlt;
  c2_i_hoistedGlobal = *c2_b_Pcc;
  c2_j_hoistedGlobal = *c2_b_N1;
  c2_k_hoistedGlobal = *c2_b_N2;
  c2_l_hoistedGlobal = *c2_b_Tlt;
  c2_m_hoistedGlobal = *c2_b_Tht;
  c2_n_hoistedGlobal = *c2_b_Td;
  c2_o_hoistedGlobal = *c2_b_Tfin;
  c2_Thc = c2_hoistedGlobal;
  c2_Tlc = c2_b_hoistedGlobal;
  c2_Tcc = c2_c_hoistedGlobal;
  c2_mfan = c2_d_hoistedGlobal;
  c2_mhc = c2_e_hoistedGlobal;
  c2_mf = c2_f_hoistedGlobal;
  c2_mht = c2_g_hoistedGlobal;
  c2_mlt = c2_h_hoistedGlobal;
  c2_Pcc = c2_i_hoistedGlobal;
  c2_N1 = c2_j_hoistedGlobal;
  c2_N2 = c2_k_hoistedGlobal;
  c2_Tlt = c2_l_hoistedGlobal;
  c2_Tht = c2_m_hoistedGlobal;
  c2_Td = c2_n_hoistedGlobal;
  c2_Tfin = c2_o_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 36U, 36U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_R, 0U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_gamma, 1U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_gamma2, 2U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Hu, 3U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_yita, 4U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_yita_mech0, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_yita_mech1, 6U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_yita_mech2, 7U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_J1, 8U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_J2, 9U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_J3, 10U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_V, 11U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Vcc, 12U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_beita, 13U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_mcc, 14U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 15U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 16U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Thc, 17U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Tlc, 18U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Tcc, 19U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_mfan, 20U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_mhc, 21U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_mf, 22U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_mht, 23U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_mlt, 24U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Pcc, 25U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_N1, 26U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_N2, 27U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Tlt, 28U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Tht, 29U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Td, 30U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Tfin, 31U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dotTcc, 32U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dotN1, 33U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dotN2, 34U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dotPcc, 35U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  c2_R = 0.28670586206896553;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_gamma = 1.4;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  c2_gamma2 = 1.39;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  c2_Hu = 43124.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
  c2_yita = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_yita_mech0 = 0.86;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_yita_mech1 = 0.91;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_yita_mech2 = 0.89;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  c2_J1 = 40.25;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  c2_J2 = 5.175;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  c2_J3 = 333.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  c2_V = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_Vcc = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
  c2_beita = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
  c2_mcc = c2_mhc + c2_mf;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
  c2_A = c2_cp_hotgas(chartInstance, c2_Tcc);
  c2_x = c2_A;
  c2_b_x = c2_x;
  c2_c_x = c2_b_x;
  c2_y = c2_c_x / 1.39;
  c2_b_A = ((c2_cp_air(chartInstance, c2_Thc) * c2_Thc * c2_mhc + 43124.0 *
             c2_mf) - c2_cp_hotgas(chartInstance, c2_Tcc) * c2_Tcc * c2_mht) -
    c2_y * c2_Tcc * ((c2_mhc + c2_mf) - c2_mht);
  c2_B = c2_cp_hotgas(chartInstance, c2_Tcc);
  c2_d_x = c2_b_A;
  c2_b_y = c2_B;
  c2_e_x = c2_d_x;
  c2_c_y = c2_b_y;
  c2_f_x = c2_e_x;
  c2_d_y = c2_c_y;
  c2_e_y = c2_f_x / c2_d_y;
  c2_c_A = c2_e_y;
  c2_g_x = c2_c_A;
  c2_h_x = c2_g_x;
  c2_i_x = c2_h_x;
  c2_f_y = c2_i_x / 1.39;
  c2_d_A = c2_f_y;
  c2_b_B = c2_mcc;
  c2_j_x = c2_d_A;
  c2_g_y = c2_b_B;
  c2_k_x = c2_j_x;
  c2_h_y = c2_g_y;
  c2_l_x = c2_k_x;
  c2_i_y = c2_h_y;
  c2_dotTcc = c2_l_x / c2_i_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
  c2_e_A = (0.91 * c2_mlt * c2_cp_hotgas(chartInstance, c2_Tht) * (c2_Tht -
             c2_Tlt) - c2_mfan * c2_cp_air(chartInstance, c2_Td) * (c2_Td -
             c2_Tfin)) - c2_mhc * c2_cp_air(chartInstance, c2_Tlc) * (c2_Tlc -
    c2_Td);
  c2_m_x = c2_e_A;
  c2_n_x = c2_m_x;
  c2_o_x = c2_n_x;
  c2_j_y = c2_o_x / 40.25;
  c2_f_A = c2_j_y;
  c2_c_B = c2_N1;
  c2_p_x = c2_f_A;
  c2_k_y = c2_c_B;
  c2_q_x = c2_p_x;
  c2_l_y = c2_k_y;
  c2_r_x = c2_q_x;
  c2_m_y = c2_l_y;
  c2_n_y = c2_r_x / c2_m_y;
  c2_g_A = c2_n_y;
  c2_s_x = c2_g_A;
  c2_t_x = c2_s_x;
  c2_u_x = c2_t_x;
  c2_dotN1 = c2_u_x / 0.010966227112321508;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
  c2_h_A = 0.89 * c2_mht * c2_cp_hotgas(chartInstance, c2_Tcc) * (c2_Tcc -
    c2_Tht) - c2_mhc * c2_cp_air(chartInstance, c2_Thc) * (c2_Thc - c2_Tlc);
  c2_v_x = c2_h_A;
  c2_w_x = c2_v_x;
  c2_x_x = c2_w_x;
  c2_o_y = c2_x_x / 5.175;
  c2_i_A = c2_o_y;
  c2_d_B = c2_N2;
  c2_y_x = c2_i_A;
  c2_p_y = c2_d_B;
  c2_ab_x = c2_y_x;
  c2_q_y = c2_p_y;
  c2_bb_x = c2_ab_x;
  c2_r_y = c2_q_y;
  c2_s_y = c2_bb_x / c2_r_y;
  c2_j_A = c2_s_y;
  c2_cb_x = c2_j_A;
  c2_db_x = c2_cb_x;
  c2_eb_x = c2_db_x;
  c2_dotN2 = c2_eb_x / 0.010966227112321508;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
  c2_k_A = c2_Pcc * c2_dotTcc;
  c2_e_B = c2_Tcc;
  c2_fb_x = c2_k_A;
  c2_t_y = c2_e_B;
  c2_gb_x = c2_fb_x;
  c2_u_y = c2_t_y;
  c2_hb_x = c2_gb_x;
  c2_v_y = c2_u_y;
  c2_w_y = c2_hb_x / c2_v_y;
  c2_l_A = 0.40138820689655175 * c2_Tcc * ((c2_mhc + c2_mf) - c2_mht);
  c2_ib_x = c2_l_A;
  c2_jb_x = c2_ib_x;
  c2_kb_x = c2_jb_x;
  c2_x_y = c2_kb_x / 2.0;
  c2_dotPcc = c2_w_y + c2_x_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -38);
  _SFD_SYMBOL_SCOPE_POP();
  *c2_b_dotTcc = c2_dotTcc;
  *c2_b_dotN1 = c2_dotN1;
  *c2_b_dotN2 = c2_dotN2;
  *c2_b_dotPcc = c2_dotPcc;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_component_model(SFc2_component_modelInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_component_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_component_modelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_dotPcc, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_dotPcc), &c2_thisId);
  sf_mex_destroy(&c2_dotPcc);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_dotPcc;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_component_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_component_modelInstanceStruct *)chartInstanceVoid;
  c2_dotPcc = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_dotPcc), &c2_thisId);
  sf_mex_destroy(&c2_dotPcc);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_component_model_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 20, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  const mxArray *c2_rhs2 = NULL;
  const mxArray *c2_lhs2 = NULL;
  const mxArray *c2_rhs3 = NULL;
  const mxArray *c2_lhs3 = NULL;
  const mxArray *c2_rhs4 = NULL;
  const mxArray *c2_lhs4 = NULL;
  const mxArray *c2_rhs5 = NULL;
  const mxArray *c2_lhs5 = NULL;
  const mxArray *c2_rhs6 = NULL;
  const mxArray *c2_lhs6 = NULL;
  const mxArray *c2_rhs7 = NULL;
  const mxArray *c2_lhs7 = NULL;
  const mxArray *c2_rhs8 = NULL;
  const mxArray *c2_lhs8 = NULL;
  const mxArray *c2_rhs9 = NULL;
  const mxArray *c2_lhs9 = NULL;
  const mxArray *c2_rhs10 = NULL;
  const mxArray *c2_lhs10 = NULL;
  const mxArray *c2_rhs11 = NULL;
  const mxArray *c2_lhs11 = NULL;
  const mxArray *c2_rhs12 = NULL;
  const mxArray *c2_lhs12 = NULL;
  const mxArray *c2_rhs13 = NULL;
  const mxArray *c2_lhs13 = NULL;
  const mxArray *c2_rhs14 = NULL;
  const mxArray *c2_lhs14 = NULL;
  const mxArray *c2_rhs15 = NULL;
  const mxArray *c2_lhs15 = NULL;
  const mxArray *c2_rhs16 = NULL;
  const mxArray *c2_lhs16 = NULL;
  const mxArray *c2_rhs17 = NULL;
  const mxArray *c2_lhs17 = NULL;
  const mxArray *c2_rhs18 = NULL;
  const mxArray *c2_lhs18 = NULL;
  const mxArray *c2_rhs19 = NULL;
  const mxArray *c2_lhs19 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1388463696U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370017086U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rdivide"), "name", "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717480U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c2_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c2_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c2_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_div"), "name", "name", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c2_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c2_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mpower"), "name", "name", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717478U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c2_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c2_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("ismatrix"), "name", "name", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1331308458U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c2_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("power"), "name", "name", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717480U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c2_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c2_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c2_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c2_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c2_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c2_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c2_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c2_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825926U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c2_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c2_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs19), "lhs", "lhs",
                  19);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
  sf_mex_destroy(&c2_rhs4);
  sf_mex_destroy(&c2_lhs4);
  sf_mex_destroy(&c2_rhs5);
  sf_mex_destroy(&c2_lhs5);
  sf_mex_destroy(&c2_rhs6);
  sf_mex_destroy(&c2_lhs6);
  sf_mex_destroy(&c2_rhs7);
  sf_mex_destroy(&c2_lhs7);
  sf_mex_destroy(&c2_rhs8);
  sf_mex_destroy(&c2_lhs8);
  sf_mex_destroy(&c2_rhs9);
  sf_mex_destroy(&c2_lhs9);
  sf_mex_destroy(&c2_rhs10);
  sf_mex_destroy(&c2_lhs10);
  sf_mex_destroy(&c2_rhs11);
  sf_mex_destroy(&c2_lhs11);
  sf_mex_destroy(&c2_rhs12);
  sf_mex_destroy(&c2_lhs12);
  sf_mex_destroy(&c2_rhs13);
  sf_mex_destroy(&c2_lhs13);
  sf_mex_destroy(&c2_rhs14);
  sf_mex_destroy(&c2_lhs14);
  sf_mex_destroy(&c2_rhs15);
  sf_mex_destroy(&c2_lhs15);
  sf_mex_destroy(&c2_rhs16);
  sf_mex_destroy(&c2_lhs16);
  sf_mex_destroy(&c2_rhs17);
  sf_mex_destroy(&c2_lhs17);
  sf_mex_destroy(&c2_rhs18);
  sf_mex_destroy(&c2_lhs18);
  sf_mex_destroy(&c2_rhs19);
  sf_mex_destroy(&c2_lhs19);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_u)), false);
  return c2_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 7, 0U, 0U, 0U, 0), false);
  return c2_y;
}

static real_T c2_cp_air(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_T)
{
  real_T c2_cp_a;
  uint32_T c2_debug_family_var_map[10];
  real_T c2_cp1;
  real_T c2_cp2;
  real_T c2_cp3;
  real_T c2_cp4;
  real_T c2_cp5;
  real_T c2_cp6;
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c2_b_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp1, 0U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp2, 1U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp3, 2U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp4, 3U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp5, 4U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_cp6, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_T, 8U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_cp_a, 9U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_cp1 = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_cp2 = 9.1483000000000008E-14;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_cp3 = -4.5693000000000004E-10;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_cp4 = 7.2934E-7;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_cp5 = -0.00024988;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_cp6 = 1.0254;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
  c2_cp_a = (((9.1483000000000008E-14 * c2_mpower(chartInstance, c2_T)
               + -4.5693000000000004E-10 * c2_b_mpower(chartInstance, c2_T)) +
              7.2934E-7 * c2_c_mpower(chartInstance, c2_T)) + -0.00024988 * c2_T)
    + c2_cp6;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -44);
  _SFD_SYMBOL_SCOPE_POP();
  return c2_cp_a;
}

static void c2_eml_scalar_eg(SFc2_component_modelInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real_T c2_mpower(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_a)
{
  real_T c2_b_a;
  real_T c2_c_a;
  real_T c2_ak;
  real_T c2_d_a;
  real_T c2_ar;
  c2_b_a = c2_a;
  c2_c_a = c2_b_a;
  c2_eml_scalar_eg(chartInstance);
  c2_ak = c2_c_a;
  c2_d_a = c2_ak;
  c2_eml_scalar_eg(chartInstance);
  c2_ar = c2_d_a;
  return muDoubleScalarPower(c2_ar, 4.0);
}

static real_T c2_b_mpower(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_a)
{
  real_T c2_b_a;
  real_T c2_c_a;
  real_T c2_ak;
  real_T c2_d_a;
  real_T c2_ar;
  c2_b_a = c2_a;
  c2_c_a = c2_b_a;
  c2_eml_scalar_eg(chartInstance);
  c2_ak = c2_c_a;
  c2_d_a = c2_ak;
  c2_eml_scalar_eg(chartInstance);
  c2_ar = c2_d_a;
  return muDoubleScalarPower(c2_ar, 3.0);
}

static real_T c2_c_mpower(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_a)
{
  real_T c2_b_a;
  real_T c2_c_a;
  real_T c2_ak;
  real_T c2_d_a;
  c2_b_a = c2_a;
  c2_c_a = c2_b_a;
  c2_eml_scalar_eg(chartInstance);
  c2_ak = c2_c_a;
  c2_d_a = c2_ak;
  c2_eml_scalar_eg(chartInstance);
  return c2_d_a * c2_d_a;
}

static real_T c2_cp_hotgas(SFc2_component_modelInstanceStruct *chartInstance,
  real_T c2_T)
{
  real_T c2_cp_hg;
  uint32_T c2_debug_family_var_map[10];
  real_T c2_cp1;
  real_T c2_cp2;
  real_T c2_cp3;
  real_T c2_cp4;
  real_T c2_cp5;
  real_T c2_cp6;
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c2_c_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp1, 0U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp2, 1U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp3, 2U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp4, 3U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_cp5, 4U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_cp6, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_T, 8U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_cp_hg, 9U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
  c2_cp1 = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
  c2_cp2 = 8.8523E-14;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
  c2_cp3 = -4.4082999999999997E-10;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
  c2_cp4 = 6.9107E-7;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
  c2_cp5 = -0.000181;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
  c2_cp6 = 1.0453;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 48);
  c2_cp_hg = (((8.8523E-14 * c2_mpower(chartInstance, c2_T)
                + -4.4082999999999997E-10 * c2_b_mpower(chartInstance, c2_T)) +
               6.9107E-7 * c2_c_mpower(chartInstance, c2_T)) + -0.000181 * c2_T)
    + c2_cp6;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -48);
  _SFD_SYMBOL_SCOPE_POP();
  return c2_cp_hg;
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_component_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_component_modelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_c_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i0, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_component_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_component_modelInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_d_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_component_model, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_component_model), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_component_model);
  return c2_y;
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_component_modelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_component_modelInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_component_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3216766106U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1808979539U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(786570073U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2343326738U);
}

mxArray *sf_c2_component_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("OPgdq5yIaLcETtf4BXokcG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,15,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_component_model_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_component_model_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_component_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[16],T\"dotN1\",},{M[1],M[23],T\"dotN2\",},{M[1],M[18],T\"dotPcc\",},{M[1],M[5],T\"dotTcc\",},{M[8],M[0],T\"is_active_c2_component_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_component_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_component_modelInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_component_modelInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _component_modelMachineNumber_,
           2,
           1,
           1,
           0,
           19,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_component_modelMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_component_modelMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _component_modelMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Thc");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Tlc");
          _SFD_SET_DATA_PROPS(2,2,0,1,"dotTcc");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Tcc");
          _SFD_SET_DATA_PROPS(4,1,1,0,"mfan");
          _SFD_SET_DATA_PROPS(5,1,1,0,"mhc");
          _SFD_SET_DATA_PROPS(6,1,1,0,"mf");
          _SFD_SET_DATA_PROPS(7,1,1,0,"mht");
          _SFD_SET_DATA_PROPS(8,1,1,0,"mlt");
          _SFD_SET_DATA_PROPS(9,1,1,0,"Pcc");
          _SFD_SET_DATA_PROPS(10,1,1,0,"N1");
          _SFD_SET_DATA_PROPS(11,1,1,0,"N2");
          _SFD_SET_DATA_PROPS(12,1,1,0,"Tlt");
          _SFD_SET_DATA_PROPS(13,1,1,0,"Tht");
          _SFD_SET_DATA_PROPS(14,1,1,0,"Td");
          _SFD_SET_DATA_PROPS(15,2,0,1,"dotN1");
          _SFD_SET_DATA_PROPS(16,2,0,1,"dotN2");
          _SFD_SET_DATA_PROPS(17,2,0,1,"dotPcc");
          _SFD_SET_DATA_PROPS(18,1,1,0,"Tfin");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,3,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1656);
        _SFD_CV_INIT_EML_FCN(0,1,"cp_air",1657,-1,1857);
        _SFD_CV_INIT_EML_FCN(0,2,"cp_hotgas",1858,-1,2041);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c2_Thc;
          real_T *c2_Tlc;
          real_T *c2_dotTcc;
          real_T *c2_Tcc;
          real_T *c2_mfan;
          real_T *c2_mhc;
          real_T *c2_mf;
          real_T *c2_mht;
          real_T *c2_mlt;
          real_T *c2_Pcc;
          real_T *c2_N1;
          real_T *c2_N2;
          real_T *c2_Tlt;
          real_T *c2_Tht;
          real_T *c2_Td;
          real_T *c2_dotN1;
          real_T *c2_dotN2;
          real_T *c2_dotPcc;
          real_T *c2_Tfin;
          c2_Tfin = (real_T *)ssGetInputPortSignal(chartInstance->S, 14);
          c2_dotPcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c2_dotN2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c2_dotN1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c2_Td = (real_T *)ssGetInputPortSignal(chartInstance->S, 13);
          c2_Tht = (real_T *)ssGetInputPortSignal(chartInstance->S, 12);
          c2_Tlt = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
          c2_N2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 10);
          c2_N1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
          c2_Pcc = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
          c2_mlt = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
          c2_mht = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c2_mf = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c2_mhc = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c2_mfan = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c2_Tcc = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c2_dotTcc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c2_Tlc = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c2_Thc = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c2_Thc);
          _SFD_SET_DATA_VALUE_PTR(1U, c2_Tlc);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_dotTcc);
          _SFD_SET_DATA_VALUE_PTR(3U, c2_Tcc);
          _SFD_SET_DATA_VALUE_PTR(4U, c2_mfan);
          _SFD_SET_DATA_VALUE_PTR(5U, c2_mhc);
          _SFD_SET_DATA_VALUE_PTR(6U, c2_mf);
          _SFD_SET_DATA_VALUE_PTR(7U, c2_mht);
          _SFD_SET_DATA_VALUE_PTR(8U, c2_mlt);
          _SFD_SET_DATA_VALUE_PTR(9U, c2_Pcc);
          _SFD_SET_DATA_VALUE_PTR(10U, c2_N1);
          _SFD_SET_DATA_VALUE_PTR(11U, c2_N2);
          _SFD_SET_DATA_VALUE_PTR(12U, c2_Tlt);
          _SFD_SET_DATA_VALUE_PTR(13U, c2_Tht);
          _SFD_SET_DATA_VALUE_PTR(14U, c2_Td);
          _SFD_SET_DATA_VALUE_PTR(15U, c2_dotN1);
          _SFD_SET_DATA_VALUE_PTR(16U, c2_dotN2);
          _SFD_SET_DATA_VALUE_PTR(17U, c2_dotPcc);
          _SFD_SET_DATA_VALUE_PTR(18U, c2_Tfin);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _component_modelMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "5pdgkEaysBnKFLgoKE3o7G";
}

static void sf_opaque_initialize_c2_component_model(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_component_modelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_component_model((SFc2_component_modelInstanceStruct*)
    chartInstanceVar);
  initialize_c2_component_model((SFc2_component_modelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_component_model(void *chartInstanceVar)
{
  enable_c2_component_model((SFc2_component_modelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_component_model(void *chartInstanceVar)
{
  disable_c2_component_model((SFc2_component_modelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_component_model(void *chartInstanceVar)
{
  sf_gateway_c2_component_model((SFc2_component_modelInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_component_model(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_component_model
    ((SFc2_component_modelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_component_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_component_model(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c2_component_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_component_model((SFc2_component_modelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_component_model(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_component_model(S);
}

static void sf_opaque_set_sim_state_c2_component_model(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_component_model(S, st);
}

static void sf_opaque_terminate_c2_component_model(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_component_modelInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_component_model_optimization_info();
    }

    finalize_c2_component_model((SFc2_component_modelInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_component_model((SFc2_component_modelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_component_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c2_component_model((SFc2_component_modelInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_component_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_component_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 13, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 14, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,15);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 15; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4253615768U));
  ssSetChecksum1(S,(1768420350U));
  ssSetChecksum2(S,(4252517335U));
  ssSetChecksum3(S,(1381716380U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_component_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_component_model(SimStruct *S)
{
  SFc2_component_modelInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_component_modelInstanceStruct *)utMalloc(sizeof
    (SFc2_component_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_component_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_component_model;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_component_model;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_component_model;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_component_model;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_component_model;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_component_model;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_component_model;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_component_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_component_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_component_model;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_component_model;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_component_model_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_component_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_component_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_component_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_component_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
