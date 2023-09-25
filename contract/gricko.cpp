#include <eosio/eosio.hpp>
#include <eosio/singleton.hpp>
using namespace eosio;

CONTRACT gricko : public contract {
   public:
      using contract::contract;

      const uint16_t TICK = 20;

   TABLE Pet{
      int8_t food;
      int8_t happiness;
      uint32_t last_aligned;
   };
   using pets_table = singleton<"pets"_n, Pet>;

   Pet realignPet(Pet pet){
      uint32_t now = current_time_point().sec_since_epoch();
      uint32_t secondsSinceLastAlignment = now - pet.last_aligned;
      uint32_t remainder = secondsSinceLastAlignment % TICK;
      int8_t tickLoss = secondsSinceLastAlignment / TICK;
      
      pet.food = std::max(0, pet.food  - tickLoss);
      pet.happiness = std::max(0, pet.happiness  - tickLoss);
      pet.last_aligned = now - remainder;

      check(pet.food > 0,"dead_food");   
      check(pet.happiness > 0,"dead_happiness"); 

      return pet;
      }

   ACTION create(name owner){
      require_auth(owner);

      pets_table pets(get_self(), owner.value);
      pets.set(Pet{
         .food = 100,
         .happiness = 100,
         .last_aligned = current_time_point().sec_since_epoch()
      }, owner);
   }


   ACTION feed(name owner){
   require_auth(owner);

   pets_table pets(get_self(), owner.value);
   check(pets.exists(),"no_pet");

   Pet pet = realignPet(pets.get());
   pet.food = std::min(100, pet.food + 10);
   pets.set(pet, owner);
}

   ACTION play(name owner){

       require_auth(owner);

   pets_table pets(get_self(), owner.value);
   check(pets.exists(),"no_pet");
   
   Pet pet = realignPet(pets.get());
   pet.happiness = std::min(100, pet.happiness +10);
   pets.set(pet, owner);

   }

};