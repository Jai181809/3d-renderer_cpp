test1 : [just after antialising]
    1200 x 675
    time to render plus write = 1884.28 (milli seconds)
    with conversion : arnd 3.4 seconds
    random rays = 16

test2 : [converting p3- p6]
    1200 x 675
    total time 1.074 second(dropped from 3.4)

test 3:
    pure rendering time with ssp :
    1000 : 57secs
    100: 4.71 secs
    64: 3.6005 secs

test 4 : [multi threading(all 16)]
    spp : 100
    an average about 0.365045 seconds (almost 16 times faster)