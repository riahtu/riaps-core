include_directories(include)

add_library(globalestimator SHARED src/GlobalEstimator.cc
        src/base/GlobalEstimatorBase.cc
        include/messages/distributedestimator.capnp.c++)

add_library(localestimator SHARED src/LocalEstimator.cc
        src/base/LocalEstimatorBase.cc
        include/messages/distributedestimator.capnp.c++
        )

add_library(sensor SHARED src/Sensor.cc
        src/base/SensorBase.cc
        include/messages/distributedestimator.capnp.c++
        )

target_link_libraries(localestimator czmq riaps dl capnp kj )
target_link_libraries(globalestimator czmq riaps dl capnp kj)
target_link_libraries(sensor czmq riaps dl capnp kj)

# add_executable(actor_prod src/prod/producer.cc
#                          src/messages.cc)

#target_link_libraries(comp_prod czmq riaps)
#target_link_libraries(actor_prod czmq riaps dl)

#add_library(comp_sub SHARED src/cons/comp_sub.cc)
#add_library(comp_rep SHARED src/cons/comp_rep.cc)
#add_executable(actor_cons src/cons/consumer.cc
 #src/messages.cc)

#target_link_libraries(comp_sub czmq riaps)
#target_link_libraries(comp_rep czmq riaps)


#target_link_libraries(actor_cons czmq riaps)