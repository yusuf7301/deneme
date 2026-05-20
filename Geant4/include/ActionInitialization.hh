#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    virtual ~ActionInitialization();

    // Çoklu çekirdek (Multi-threading) kullanımında ana iş parçacığı için
    virtual void BuildForMaster() const;
    
    // Her bir iş parçacığında çalışacak eylemleri tanımladığımız ana fonksiyon
    virtual void Build() const;
};

#endif