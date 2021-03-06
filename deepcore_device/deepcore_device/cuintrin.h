#ifndef __cuintrin_h__
#define __cuintrin_h__

#if defined(_M_X64)||defined(_M_AMD64)||defined(__x86_64)||defined(_M_IA64)||defined(__LP64__)
#define PTX_PTR "l"
#else
#define PTX_PTR "r"
#endif

__device__ __forceinline__ unsigned int __laneid()
{
    unsigned int lane;
    asm volatile ( "mov.u32 %0, %%laneid;" : "=r"(lane) );
    return lane;
}
__device__ __forceinline__ unsigned int __imad( unsigned int a, unsigned int b, unsigned int c )
{
    unsigned int d;
    asm volatile ( "mad.lo.u32 %0, %1, %2, %3;" : "=r"(d) : "r"(a), "r"(b), "r"(c) );
    return d;
}

#if CUDA_ARCH>=70
#define SHFL_XOR(val,delta,n) __shfl_xor_sync(0xffffffff,val,delta,n)
#define SHFL(val,delta,n)     __shfl_sync(0xffffffff,val,delta,n)
#else
#define SHFL_XOR(val,delta,n) __shfl_xor(val,delta,n)
#define SHFL(val,delta,n)     __shfl(val,delta,n)
#endif

#endif