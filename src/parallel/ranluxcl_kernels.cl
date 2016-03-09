//If the include does not work then the contents of the ranluxcl.cl file can
//just be pasted here at the top instead.
#include "ranluxcl.cl"

__kernel void kernelInit(
	private uint32_t ins,
	global ranluxcl_state_t *ranluxcltab)
{
	ranluxcl_initialization(ins, ranluxcltab);
}

__kernel void kernelPurn(
	global ranluxcl_state_t *ranluxcltab,
	global float4 *prns)
{
	//Downloading ranluxcltab. The state of RANLUXCL is stored in ranluxclstate.
	ranluxcl_state_t ranluxclstate;
	ranluxcl_download_seed(&ranluxclstate, ranluxcltab);

	for(int i=0; i<GEN_PER_IT; i++){
		prns[get_global_id(0) + i * get_global_size(0)] =
			ranluxcl32(&ranluxclstate);
	}

	//Important to upload the state again
	ranluxcl_upload_seed(&ranluxclstate, ranluxcltab);
}

__kernel void kernelPnrn(
	global ranluxcl_state_t *ranluxcltab,
	global float4 *prns)
{
	//Downloading ranluxcltab. The state of RANLUXCL is stored in ranluxclstate.
	ranluxcl_state_t ranluxclstate;
	ranluxcl_download_seed(&ranluxclstate, ranluxcltab);

	for(int i=0; i<GEN_PER_IT; i++){
		prns[get_global_id(0) + i * get_global_size(0)] =
			ranluxcl32norm(&ranluxclstate);
	}

	//Important to upload the state again
	ranluxcl_upload_seed(&ranluxclstate, ranluxcltab);
}