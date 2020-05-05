## Model conversion 
The xxd tool is used to convert the model from tflite to C file:
<https://linux.die.net/man/1/xxd>

```
xxd -i temp_model.tflite >  temp_model_data.cc
```


## Compilation
```
mbed deploy

mbed compile -c -f  -m CY8CPROTO_062_4343W  -t GCC_ARM


cp ./BUILD/CY8CPROTO_062_4343W/GCC_ARM/tf-c.hex /Volumes/DAPLINK/
```
