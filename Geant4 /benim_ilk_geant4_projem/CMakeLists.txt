# CMake için minimum sürümü belirtir
cmake_minimum_required(VERSION 3.16)

# Proje adını tanımlar
project(BenimIlkGeant4Projem)

# Geant4 paketini zorunlu olarak bulur
find_package(Geant4 REQUIRED)

# Geant4 tarafından sağlanan ayarları projeye dahil eder
include(${Geant4_USE_FILE})

# Başlık dosyalarının bulunduğu klasörü derleyiciye tanıtır
include_directories(${PROJECT_SOURCE_DIR}/include)

# main.cc dosyasını ve src klasöründeki tüm .cc dosyalarını kaynak listesine ekler
file(GLOB sources
    ${PROJECT_SOURCE_DIR}/main.cc
    ${PROJECT_SOURCE_DIR}/src/*.cc
)

# include klasöründeki tüm .hh dosyalarını yardımcı liste olarak toplar
file(GLOB headers
    ${PROJECT_SOURCE_DIR}/include/*.hh
)

# Çalıştırılabilir program hedefini oluşturur
add_executable(benim_ilk_geant4 ${sources} ${headers})

# Bu hedefi Geant4 kütüphanelerine bağlar
target_link_libraries(benim_ilk_geant4 ${Geant4_LIBRARIES})

# vis.mac dosyasını build klasörüne kopyalar
configure_file(
    ${PROJECT_SOURCE_DIR}/vis.mac
    ${PROJECT_BINARY_DIR}/vis.mac
    COPYONLY
)

# İstersen ileride başka macro dosyalarını da bu şekilde kopyalayabilirsin

# Derleme sonrası kullanıcıya hedefin adını standart kurulum mantığına eklemek için tanımlar
install(TARGETS benim_ilk_geant4 DESTINATION bin)