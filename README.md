# Parameter Tool Box

A tool box for parameter and value processing.

## Building the project

Execute the following commands on cli.

```
git clone /path/to/param-tool-box.git
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../param-tool-box
cmake --build .
```

> Linux: ```cmake -DCMAKE_BUILD_TYPE=[Debug|Release] ../param-tool-box```
> macOS:```cmake -GXcode ../param-tool-box```
> Windows 10: ```cmake -G"Visual Studio 16 2019" -A x64 ..\param-tool-box```

## Using the tools and examples

### Ramp processor

The ```ptb::ramp_processor``` can take a list of automation curve points and interpolate between them. This allows sample accurate automation curve processing. By providing it a lambda function to retrieve the automation curve points, the class is not bound to any list implementation.

In order to use it with ```Vst::IParamValueQueue```, do as follows:

```
ptb::ramp_processor create_ramp_processor(Vst::IParamValueQueue* queue, float initValue)
{
    // Create lambda for Vst::IParamValueQueue ...
    const auto pvqp = [queue](int index, int& offset, ptb::ramp_processor::mut_ValueType& value) {
        if (!queue)
            return false;

        if (index < queue->getPointCount())
        {
            Vst::ParamValue tmpValue = 0.;
            int32 offset    tmpOffset = 0;
            if (queue->getPoint(index, tmpOffset, tmpValue) != kResultOk)
                return false;

            offset = tmpOffset;
            value = tmpValue;
            return true;
        }

        return false;
    };

    // ... and pass it to the ptb::ramp_processor!
    return ptb::ramp_processor(pvqp, initValue);
}

//-------------------------------------------------------------------
Steinberg::tresult MyPlugin::process(Vst::ProcessData& data)
{
    // Get Vst::IParamValueQueue from data.paramChanges
    IParamValueQueue* myParamQueue = ...

    // Create a stack object of ptb::ramp_processor
    ptb::ramp_processor myParamProcessor = create_ramp_processor(myParamQueue, m_lastValue);

    for(...)
    {
        (*output)++ = (*input)++ * myParamProcessor.getValue();

        myParamProcessor.advance();
    }
}
```

## License

Copyright 2021 Hansen Audio

Licensed under the MIT: https://mit-license.org/