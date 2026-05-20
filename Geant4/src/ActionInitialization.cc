#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
    // Veri toplama (RunAction) sınıfı yazarsak buraya da ekleyeceğiz.
    // Şimdilik boş kalabilir.
}

void ActionInitialization::Build() const {
    // 3. adımda yazdığımız parçacık tabancasını (Karbon-14) sisteme kaydediyoruz.
    SetUserAction(new PrimaryGeneratorAction());
    
    SetUserAction(new SteppingAction()); // Dedektifimizi sisteme dahil ettik!
    
    // Not: 5. Adımda SteppingAction yazdığımızda onu da buraya şu şekilde ekleyeceğiz:
    // SetUserAction(new SteppingAction());
}