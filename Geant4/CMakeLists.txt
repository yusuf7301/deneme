cmake_minimum_required(VERSION 3.16...3.27)
project(BetaDecaySim)

# Geant4 kütüphanelerini bul
find_package(Geant4 REQUIRED ui_all vis_all)

# Geant4 ayarlarını projeye dahil et
include(${Geant4_USE_FILE})

# Kendi yazdığımız include klasörünü sisteme tanıt
include_directories(${PROJECT_SOURCE_DIR}/include)

# src klasöründeki tüm .cc dosyalarını bul
file(GLOB SOURCES "src/*.cc")
file(GLOB HEADERS "include/*.hh")

# sim.cc (ana dosya) ve diğer dosyaları birleştirip "BetaDecay" adında bir program üret
add_executable(BetaDecay sim.cc ${SOURCES} ${HEADERS})

# Geant4 kütüphanelerini programımıza bağla
target_link_libraries(BetaDecay ${Geant4_LIBRARIES})