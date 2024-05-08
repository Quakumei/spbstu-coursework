import pycuda.driver as cuda
import pycuda.autoinit
from pycuda.compiler import SourceModule
import numpy as np

# Define the CUDA kernel that will add the two arrays
mod = SourceModule("""
    __global__ void add_arrays(float *a, float *b, float *c, int n)
    {
        int idx = threadIdx.x + blockDim.x * blockIdx.x;
        if (idx < n)
            c[idx] = a[idx] + b[idx];
    }
""")

# Get the kernel function from the compiled module
add_arrays = mod.get_function("add_arrays")

# Set the array size
n = 10

# Generate random input data
a = np.random.randn(n).astype(np.float32)
b = np.random.randn(n).astype(np.float32)

# Allocate device memory for the input and output arrays
a_gpu = cuda.mem_alloc(a.nbytes)
b_gpu = cuda.mem_alloc(b.nbytes)
c_gpu = cuda.mem_alloc(b.nbytes)

# Copy the input data to the device
cuda.memcpy_htod(a_gpu, a)
cuda.memcpy_htod(b_gpu, b)

# Calculate the block and grid sizes for the kernel
block_size = 128
grid_size = (n + block_size - 1) // block_size

# Launch the kernel
add_arrays(a_gpu, b_gpu, c_gpu, np.int32(n), block=(block_size,1,1), grid=(grid_size,1))

# Copy the result back to the host
c = np.empty_like(a)
cuda.memcpy_dtoh(c, c_gpu)

# Print the results
print("a:", a)
print("b:", b)
print("c:", c)