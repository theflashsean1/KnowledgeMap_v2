cmake_minimum_required(VERSION 3.7)
project(KnowledgeMap_v2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/KRI.cpp src/KRI.h src/KRI/Indiv.cpp src/KRI/Indiv.h src/KRI/FuncMap.cpp src/KRI/FuncMap.h src/KRL/PrimitiveSymbol.cpp src/KRL/PrimitiveSymbol.h src/KRL/Term.cpp src/KRL/Term.h src/KRI/PredMap.cpp src/KRI/PredMap.h src/KRL/Formula.cpp src/KRL/Formula.h src/KRL.cpp src/KRL.h src/KRI/VarAssign.cpp src/KRI/VarAssign.h)
add_executable(KnowledgeMap_v2 ${SOURCE_FILES})