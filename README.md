##
Based on Maclain Lobdell branch
add-cy8cproto-capsense-slider 
```
mbed deploy

--compile without TF calls and flash to board:
mbed compile -c  -f -m CY8CPROTO_062_4343W  -t GCC_ARM

--compile with TF calls and flash to board:
mbed compile -c -f  -DTF_MICRO  -m CY8CPROTO_062_4343W  -t GCC_ARM


cp ./BUILD/CY8CPROTO_062_4343W/GCC_ARM/tf-c.hex /Volumes/DAPLINK/
```
