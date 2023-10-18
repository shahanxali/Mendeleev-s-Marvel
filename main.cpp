#include<bits/stdc++.h>
using namespace std;



//creating the blueprint of the elements (properties)

class Element {
public:
    int AtomicNumber;
    string AtomicName;
    string Symbol;
    vector<int> Color;
    vector<int> Range;

};



//function to call and assign values when called

Element create(int atomicNumber, const string& atomicName,string symbol, const vector<int>& color, const vector<int>& range) {
    Element element;
    element.AtomicNumber = atomicNumber;
    element.Symbol = symbol;
    element.AtomicName = atomicName;
    element.Color = color;
    element.Range = range;
    return element;
}


// Declare elements as global variable

//45 elements rn
Element hydrogen, helium, lithium, beryllium, boron, carbon, nitrogen, oxygen, fluorine, neon, sodium,
magnesium, aluminum, silicon, phosphorus, sulfur, chlorine, argon, potassium, calcium, scandium,
titanium, vanadium, chromium, manganese, iron, cobalt, nickel, copper, zinc, gallium, germanium,
arsenic, selenium, bromine, krypton, rubidium, strontium, yttrium, zirconium, niobium, molybdenum,
technetium, ruthenium;






map<int, string> elementMap;



//to assign all the elements as call one by one to give every element properties

//45 at the moment

void properties() {

    hydrogen = create(1, "Hydrogen", "H", {1, 1, 1}, {0, 0, 0});
    elementMap[hydrogen.AtomicNumber]="hydrogen";

    helium = create(2, "Helium", "He", {0, 0, 255}, {0, 0, 0});
    elementMap[helium.AtomicNumber]="helium";

    lithium = create(3, "Lithium", "Li", {0, 0, 55}, {0, 0, 0});
    elementMap[lithium.AtomicNumber]="lithium";

    beryllium = create(4, "Beryllium", "Be", {0, 128, 0}, {0, 0, 0});
    elementMap[beryllium.AtomicNumber] = "beryllium";

    boron = create(5, "Boron", "B", {255, 165, 0}, {0, 0, 0});
    elementMap[boron.AtomicNumber] = "boron";

    carbon = create(6, "Carbon", "C", {0, 0, 0}, {0, 0, 0});
    elementMap[carbon.AtomicNumber] = "carbon";

    nitrogen = create(7, "Nitrogen", "N", {0, 0, 255}, {0, 0, 0});
    elementMap[nitrogen.AtomicNumber] = "nitrogen";

    oxygen = create(8, "Oxygen", "O", {255, 0, 0}, {0, 0, 0});
    elementMap[oxygen.AtomicNumber] = "oxygen";

    fluorine = create(9, "Fluorine", "F", {0, 255, 0}, {0, 0, 0});
    elementMap[fluorine.AtomicNumber] = "fluorine";

    neon = create(10, "Neon", "Ne", {255, 0, 0}, {0, 0, 0});
    elementMap[neon.AtomicNumber] = "neon";

    sodium = create(11, "Sodium", "Na", {255, 0, 0}, {0, 0, 0});
    elementMap[sodium.AtomicNumber] = "sodium";

    magnesium = create(12, "Magnesium", "Mg", {0, 128, 0}, {0, 0, 0});
    elementMap[magnesium.AtomicNumber] = "magnesium";

    aluminum = create(13, "Aluminum", "Al", {128, 128, 128}, {0, 0, 0});
    elementMap[aluminum.AtomicNumber] = "aluminum";

    silicon = create(14, "Silicon", "Si", {128, 128, 128}, {0, 0, 0});
    elementMap[silicon.AtomicNumber] = "silicon";

    phosphorus = create(15, "Phosphorus", "P", {255, 0, 0}, {0, 0, 0});
    elementMap[phosphorus.AtomicNumber] = "phosphorus";

    sulfur = create(16, "Sulfur", "S", {255, 255, 0}, {0, 0, 0});
    elementMap[sulfur.AtomicNumber] = "sulfur";

    chlorine = create(17, "Chlorine", "Cl", {0, 255, 0}, {0, 0, 0});
    elementMap[chlorine.AtomicNumber] = "chlorine";

    argon = create(18, "Argon", "Ar", {0, 0, 128}, {0, 0, 0});
    elementMap[argon.AtomicNumber] = "argon";

    potassium = create(19, "Potassium", "K", {128, 0, 128}, {0, 0, 0});
    elementMap[potassium.AtomicNumber] = "potassium";

    calcium = create(20, "Calcium", "Ca", {0, 128, 128}, {0, 0, 0});
    elementMap[calcium.AtomicNumber] = "calcium";

    scandium = create(21, "Scandium", "Sc", {139, 0, 139}, {0, 0, 0});
    elementMap[scandium.AtomicNumber] = "scandium";

    titanium = create(22, "Titanium", "Ti", {0, 206, 209}, {0, 0, 0});
    elementMap[titanium.AtomicNumber] = "titanium";

    vanadium = create(23, "Vanadium", "V", {255, 0, 0}, {0, 0, 0});
    elementMap[vanadium.AtomicNumber] = "vanadium";

    chromium = create(24, "Chromium", "Cr", {139, 0, 0}, {0, 0, 0});
    elementMap[chromium.AtomicNumber] = "chromium";

    manganese = create(25, "Manganese", "Mn", {0, 139, 0}, {0, 0, 0});
    elementMap[manganese.AtomicNumber] = "manganese";

    iron = create(26, "Iron", "Fe", {139, 69, 19}, {0, 0, 0});
    elementMap[iron.AtomicNumber] = "iron";

    cobalt = create(27, "Cobalt", "Co", {0, 0, 128}, {0, 0, 0});
    elementMap[cobalt.AtomicNumber] = "cobalt";

    nickel = create(28, "Nickel", "Ni", {0, 128, 128}, {0, 0, 0});
    elementMap[nickel.AtomicNumber] = "nickel";

    copper = create(29, "Copper", "Cu", {255, 140, 0}, {0, 0, 0});
    elementMap[copper.AtomicNumber] = "copper";

    zinc = create(30, "Zinc", "Zn", {128, 0, 0}, {0, 0, 0});
    elementMap[zinc.AtomicNumber] = "zinc";

    gallium = create(31, "Gallium", "Ga", {128, 0, 128}, {0, 0, 0});
    elementMap[gallium.AtomicNumber] = "gallium";

    germanium = create(32, "Germanium", "Ge", {0, 128, 0}, {0, 0, 0});
    elementMap[germanium.AtomicNumber] = "germanium";

    arsenic = create(33, "Arsenic", "As", {0, 255, 0}, {0, 0, 0});
    elementMap[arsenic.AtomicNumber] = "arsenic";

    selenium = create(34, "Selenium", "Se", {255, 0, 0}, {0, 0, 0});
    elementMap[selenium.AtomicNumber] = "selenium";

    bromine = create(35, "Bromine", "Br", {0, 0, 139}, {0, 0, 0});
    elementMap[bromine.AtomicNumber] = "bromine";

    krypton = create(36, "Krypton", "Kr", {128, 0, 128}, {0, 0, 0});
    elementMap[krypton.AtomicNumber] = "krypton";

    rubidium = create(37, "Rubidium", "Rb", {0, 139, 139}, {0, 0, 0});
    elementMap[rubidium.AtomicNumber] = "rubidium";

    strontium = create(38, "Strontium", "Sr", {255, 0, 0}, {0, 0, 0});
    elementMap[strontium.AtomicNumber] = "strontium";

    yttrium = create(39, "Yttrium", "Y", {128, 0, 0}, {0, 0, 0});
    elementMap[yttrium.AtomicNumber] = "yttrium";

    zirconium = create(40, "Zirconium", "Zr", {0, 128, 128}, {0, 0, 0});
    elementMap[zirconium.AtomicNumber] = "zirconium";

    niobium = create(41, "Niobium", "Nb", {0, 255, 255}, {0, 0, 0});
    elementMap[niobium.AtomicNumber] = "niobium";

    molybdenum = create(42, "Molybdenum", "Mo", {0, 0, 128}, {0, 0, 0});
    elementMap[molybdenum.AtomicNumber] = "molybdenum";

    technetium = create(43, "Technetium", "Tc", {128, 128, 128}, {0, 0, 0});
    elementMap[technetium.AtomicNumber] = "technetium";

    ruthenium = create(44, "Ruthenium", "Ru", {255, 140, 0}, {0, 0, 0});
    elementMap[ruthenium.AtomicNumber] = "ruthenium";


}






//Start rendering all the called elements









//main function

int main() {
    
    properties();
    

    
    


    return 0;
}

