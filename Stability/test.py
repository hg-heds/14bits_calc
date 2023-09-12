import ctypes

for i in range(260):
    if i == 125:
        pass
    val_uns = ctypes.c_uint8(i)
    val = ctypes.c_int8(i)
    print(val, val_uns)