# Sony_Remote_Infrared_Hack
Sony Remote Infrared Hack — Capture, decode, analyze, and transmit Sony TV remote IR commands using Arduino.






```
https://robu.in/product/hx1838-vs1838-nec-infrared-ir-wireless-remote-control-sensor-module-arduino/
https://robu.in/product/arduino-nano-board-3-0-with-ch340-chip-unsoldered/
https://www.amazon.in/RMF-TX310U-Replace-Voice-Remote-Control/dp/B07ZSW42RZ

https://robu.in/product/nrf51822-ble4-0-bluetooth-2-4g-wireless-module-onboard-rev3/
```












### CHIP

```


N51822   ???    nRF51822 multi-protocol ZBluethooth Low Energy And 2.4GHz RF system-On-Chip 

20-pin STM microcontrollers   32F033F


```

### POWER

- **Protocol:** Sony
- **Address:** `0x01`
- **Command:** `0x15`
- **Raw Data:** `0x095`
- **Bits:** 12
- **Bit Order:** LSB First
- **Gap:** `3,276,750 µs` (~3.277 s)
- **Duration:** `18,950 µs` (~18.95 ms)






```
                 Sony IR frame
                       │
             ┌─────────┴─────────┐
             │                   │
         Address              Command
          0x01                  0x15
             │                   │
             └─────────┬─────────┘
                       │
                  Encoded into
                       │
                    Raw Data
                     0x095
                       │
                    12 bits

```



## Sony TV IR Commands


| Img | Button | Address | Command | Raw Data | Bits |
|---|---|---|---:|---:|---:|
| <img src="img/123.jpg" width="60"> | POWER | `0x01` | `0x15` | `0x095` | 12 |





### Help

```
https://blog.flipper.net/infrared/
https://www.youtube.com/watch?v=XUY0-doBx1U




https://github.com/marsfan/IR-Codes/tree/master
```