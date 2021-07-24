#include "rtapi.h"
#include "rtapi_ctype.h"
#include "rtapi_app.h"
#include "rtapi_string.h"
#include "rtapi_errno.h"
#include "rtapi_math64.h"
#include <rtapi_io.h>
#include "hal.h"
#include <ai.h>

/* module information */
MODULE_AUTHOR("Skynet");
MODULE_DESCRIPTION("Artificial Neural Network");
MODULE_LICENSE("GPL");

/* Usage example :
 *
 * halcmd stop
 * halcmd loadrt threads name1=base-thread fp1=0 period1=25000 name2=servo-thread period2=1000000
 * halcmd loadrt ai
 * halcmd train_ai
 * halcmd addf exec servo-thread
 * halcmd start
 *
 * To compile, see attached makefile eof.
 */

static int comp_idx;

typedef struct {
    bool ok;
} skynet_t;
skynet_t *skynet;

typedef struct {
    hal_float_t *Pin;
} float_data_t;

typedef struct {
    hal_bit_t *Pin;
} bit_data_t;
bit_data_t *bit0, *bit1, *bit2, *bit3, *bit4;

typedef struct {
    hal_float_t Pin;
} param_data_t;

typedef struct {
    hal_s32_t *Pin;
} s32_data_t;

typedef struct {
    hal_u32_t *Pin;
} u32_data_t;

typedef struct {
    hal_port_t *Pin;
} port_data_t;
port_data_t *P1,*P2;

struct ai_setup ai_setup; // Component wide data bucket
struct ai_value ai_value;

static int comp_idx;		/* component ID */

static void train_ai();
static void run_ai();
static void ai_command();

int trigger=0;

int rtapi_app_main(void) {

    int r = 0;
    comp_idx = hal_init("ai");
    if(comp_idx < 0) return comp_idx;
    r = hal_export_funct("train_ai", train_ai, &skynet,0,0,comp_idx);
    r = hal_export_funct("exec_ai", run_ai, &skynet,0,0,comp_idx);
    r = hal_export_funct("ai_command", ai_command, &skynet,0,0,comp_idx);

    bit0 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("bit0",HAL_IN,&(bit0->Pin),comp_idx);

    bit1 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("bit1",HAL_IN,&(bit1->Pin),comp_idx);

    bit2 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("bit2",HAL_OUT,&(bit2->Pin),comp_idx);

    bit3 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("train",HAL_IN,&(bit3->Pin),comp_idx);

    bit4 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("run",HAL_IN,&(bit4->Pin),comp_idx);

    if(r) {
        hal_exit(comp_idx);
    } else {
        hal_ready(comp_idx);
    }
    return 0;
}

void rtapi_app_exit(void) {
    hal_exit(comp_idx);
}

static void ai_command() // This run's at servo-thread.
{
    if(*bit3->Pin==true){
        train_ai();
        *bit3->Pin=false;
    }

    if(*bit4->Pin==true){
        run_ai();
    }
}

static void train_ai()
{
    // Neural Network parameters
    ai_setup.num_inputs = 2;
    ai_setup.num_outputs = 1;
    ai_setup.num_layers = 3;
    ai_setup.num_neurons_hidden = 3;
    ai_setup.desired_error = 0.0001;
    ai_setup.max_epochs = 500000;
    ai_setup.epochs_between_reports = 1000;
    ai_setup.train_on_file="/home/user/Desktop/AI/halcompile-ai-fann/build-ai_cpp-Desktop-Debug/xor.data";
    ai_setup.neural_network_file="xor_float.net";
    train_ai_cpp(ai_setup);

    // setp train 1
}

static void run_ai()
{
    ai_value.neural_network_file="xor_float.net";
    ai_value.Xor_in0=*bit0->Pin;
    ai_value.Xor_in1=*bit1->Pin;
    ai_value=run_ai_cpp(ai_value);
    if(ai_value.Xor_out0>=0.5){
        *bit2->Pin=true;
    } else {
        *bit2->Pin=false;
    }

    // setp run 1
}










