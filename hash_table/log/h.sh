#!/bin/bash
WORK_PATH=/home/work/zhaokunyao/code/hash_table/log
HADOOP_CLIENT_PATH=/home/work/zhaokunyao/hadoop/hadoop-client/hadoop
HADOOP_CLIENT_BIN=${HADOOP_CLIENT_PATH}/bin/hadoop
HADOOP_CLIENT_CONF=${HADOOP_CLIENT_PATH}/conf/hadoop-site.xml 
HDFS_ROOT=/app/nuomi/lvyou/zhaokunyao
HDFS_IN_PATH=${HDFS_ROOT}/
HDFS_OUT_PATH=${HDFS_IN_PATH}/h.out
INPUT="${HDFS_IN_PATH}/a.log ${HDFS_IN_PATH}/b.log"
## 检查输出目录是否存在
${HADOOP_CLIENT_BIN} fs -conf ${HADOOP_CLIENT_CONF} -test -e ${HDFS_OUT_PATH}
if [ $? -eq 0 ]; then
    echo "${HDFS_OUT_PATH}"" is exist!"
    exit 1
fi
echo 'going'

${HADOOP_CLIENT_BIN} jar /home/work//zhaokunyao/hadoop/hadoop-client/hadoop/lib/streaming-3.25.0.jar  \
-conf ${HADOOP_CLIENT_CONF} \
-D mapred.map.tasks=3 \
-D mapred.reduce.tasks=3 \
-D mapred.job.map.capacity=10 \
-D mapred.job.name="dataop_test" \
-D mapred.job.priority=LOW \
-D stream.non.zero.exit.is.failure=true \
-D stream.memory.limit=8000 \
-D mapred.job.reduce.memory.mb=8000 \
-file ${WORK_PATH}/reducer.py \
-input ${INPUT} \
-output ${HDFS_OUT_PATH} \
-mapper cat \
-reducer ./reducer.py
#-D stream.map.output.field.separator=. \
#-D stream.num.map.output.key.fields=4 \
#-D num.key.fields.for.partition=2 \
#-D map.output.key.field.separator=. \
#-D mapred.output.compress=true \
#-D mapred.output.compression.codec=org.apache.hadoop.io.compress.GzipCodec \
#-partitioner org.apache.hadoop.mapred.lib.KeyFieldBasedPartitioner \
#if [ $? -ne 0 ]; then
#    ${HADOOP_CLIENT_BIN} fs -conf ${HADOOP_CLIENT_CONF} -rmr ${HDFS_OUT_PATH}
#    exit 1
#fi
