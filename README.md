### About Project
The project is aimed to convert Tsinghua triffic sign json dataset(https://cg.cs.tsinghua.edu.cn/traffic-sign/) to VOC xml that can be supported by labelImg(https://github.com/tzutalin/labelImg). It's a disposable progrem, so I havn't made any optimization on performance, only ensure it can work properly in a single case. 

The json file in the case is uploaded below as "annotations.json"

## Tsinghua2xml
The main progrem to convert tsinghua dataset to VOC xml. Place the "annotations.json" and cpp files together and run it.

## TsinghuaAnalyze
Disabled the function of output XML and added a statistics for each label. You can know how many labels contain according this.