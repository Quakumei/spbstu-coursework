'''Testing system CUDA capabilities'''
import pycuda.driver as cuda
from pycuda.compiler import SourceModule

cuda.init()  # Initialize the CUDA system

deviceCount = cuda.Device.count()
print("Device count:", deviceCount, "\n")

for i in range(deviceCount):
    device = cuda.Device(i)
    deviceProp = device.get_attributes()
    # Выводим информацию об устройстве
    print("Device name: ", device.name())
    print("Total global memory: ", device.total_memory())
    print("Shared memory per block: ", deviceProp[cuda.device_attribute.MAX_SHARED_MEMORY_PER_BLOCK])
    print("Registers per block: ", deviceProp[cuda.device_attribute.MAX_REGISTERS_PER_BLOCK])
    print("Warp size: ", deviceProp[cuda.device_attribute.WARP_SIZE])
    # print("Memory pitch: ", deviceProp[cuda.device_attribute.MEMORY_PITCH])
    print("Max threads per block: ", deviceProp[cuda.device_attribute.MAX_THREADS_PER_BLOCK])
    print("Max threads dimensions: x = %d, y = %d, z = %d" % (deviceProp[cuda.device_attribute.MAX_BLOCK_DIM_X],
                                                               deviceProp[cuda.device_attribute.MAX_BLOCK_DIM_Y],
                                                               deviceProp[cuda.device_attribute.MAX_BLOCK_DIM_Z]))
    print("Max grid size: x = %d, y = %d, z = %d" % (deviceProp[cuda.device_attribute.MAX_GRID_DIM_X],
                                                     deviceProp[cuda.device_attribute.MAX_GRID_DIM_Y],
                                                     deviceProp[cuda.device_attribute.MAX_GRID_DIM_Z]))
    print("Clock rate: ", deviceProp[cuda.device_attribute.CLOCK_RATE])
    print("Total constant memory: ", deviceProp[cuda.device_attribute.TOTAL_CONSTANT_MEMORY])
    print("Compute capability: %d.%d" % device.compute_capability())
    print("Texture alignment: ", deviceProp[cuda.device_attribute.TEXTURE_ALIGNMENT])
    print("Device overlap: ", deviceProp[cuda.device_attribute.MAX_REGISTERS_PER_BLOCK])
    print("Multiprocessor count: ", deviceProp[cuda.device_attribute.MULTIPROCESSOR_COUNT])
    print("Kernel execution timeout enabled: ", deviceProp[cuda.device_attribute.KERNEL_EXEC_TIMEOUT])