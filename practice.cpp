#include <iostream>
#include <cassert>
#include <cmath>

/*
 * V Kocourkově se rozhodly, že systém adres domů je zastaralý a potřebují nový.
 * Protože v Kocourkově právě probíhá výzkum v oblasti automatického doručování pošty, rozhodli se systém uzpůsobit robotům.
 * Roboti neumí číst text, a proto je potřeba adresu zakódovat do čísel.
 *
 * Adresa domu se skládá z několika částí:
 * - číslo bloku
 * - číslo ulice
 * - číslo domu
 *
 * Město se skládá z několika bloků, každý blok má několik ulic a každá ulice má několik domů.
 * Bloky jsou uspořádáné ve čtvercové síti.
 * Ulice v bloku jsou pod sebou (změna osy Y)
 * Domy v ulici jsou vedle sebe (změna osy X)
 * Viz tabule.
 *
 * Každé město musím mít alespoň jeden blok, každý blok musí mít alespoň jednu ulici, každá ulice musí mít alespoň jeden dům.
 */

/*
 * Vytvořte strukturu pro definici města.
 * Potřebujete si ukládat kolik má město bloků, kolik má každý blok ulic a kolik má každá ulice domů.
 * (všechny bloky a všechny ulice jsou stejné)
 */
struct Town
{
    int blocks; // Kolik má město bloků
    int streets;
    int houses;
};

/*
 * Vytvořte strukturu pro definici adresy.
 * Potřebujete si ukládat číslo bloku, číslo ulice a číslo domu.
 */
struct Address
{
    int block;
    int street;
    int house;
};

/*
 * Napište funkci, která zkontorluje, zda je město validní.
 */
bool isTownValid(Town town)
{
    if (town.blocks > 0 && town.streets > 0 && town.houses > 0 && std::sqrt(town.blocks) * std::sqrt(town.blocks) == town.blocks)
    {
        return true;
    }

    return false;
}

/*
 * Napište funkci, která zkontroluje, zda je adresa validní.
 */
bool isAddressValid(Address address, Town town)
{
    if (address.block < town.blocks && address.street < town.streets && address.house < town.houses)
    {
        return true;
    }

    return false;
}

/*
 * Napište funkci, která vypočítá vzdálenost mezi dvěma adresami.
 * Jsou možné následující typy pohybu.
 * Pohyb mezi domy (+-X) - vzdálenost 1
 * Pohyb mezi ulicemi (+-Y) - vzdálenost 5
 * Pohyb mezi bloky (+-X, +-Y) - vzdálenost 10
 */
std::size_t distance(Address address1, Address address2, Town town)
{
    int blockDistance = 10;  // default=10
    int streetDistance = 5; // default=5
    int houseDistance = 1;  // default=1

    int streetDiff;
    int houseDiff;

    int blocksPerRow = std::sqrt(town.blocks);

    int row1 = address1.block / blocksPerRow;
    int col1 = address1.block % blocksPerRow;
    int row2 = address2.block / blocksPerRow;
    int col2 = address2.block % blocksPerRow;

    int blockDiff = std::abs(row1 - row2) + std::abs(col1 - col2);

    if (row1 == row2)
    {
        streetDiff = std::abs(address1.street - address2.street);
    }

    else // if (col1 == col2)
    {
        streetDiff = std::abs(address1.street - address2.street) + town.streets - 1;
    }
    
    int houseBetween = std::abs(address1.block - address2.block) % blocksPerRow;

    if (col1 == col2)
    {
        houseDiff = std::abs(address1.house - address2.house);
    }
    if (address1.block % blocksPerRow > address2.block % blocksPerRow)
    {
        houseDiff = address1.house + std::abs(town.houses - 1 - address2.house) + (houseBetween - 1) * (town.houses - 1);
    }
    else // if (row1 == row2)
    {
        houseDiff = std::abs(town.houses - 1 - address1.house) + address2.house + (houseBetween - 1) * (town.houses - 1);
    }

    return (blockDiff * blockDistance) + (streetDiff * streetDistance) + (houseDiff * houseDistance);
}

int main()
{
    Town validTown = {
        .blocks = 9,
        .streets = 3,
        .houses = 4,
    };

    Town invalidTown1 = {
        .blocks = 0,
        .streets = 5,
        .houses = 10,
    };

    Town invalidTown2 = {
        .blocks = 24,
        .streets = 2,
        .houses = 10,
    };

    Address validAddress1 = {
        .block = 3,  // default=0
        .street = 1, // default=1
        .house = 2,  // default=2
    };

    Address validAddress2 = {
        .block = 1,  // default=1
        .street = 2, // default=2
        .house = 3,  // default=3
    };

    Address invalidAddress1 = {
        .block = 4,
        .street = 3,
        .house = 3,
    };

    assert(isTownValid(validTown));
    assert(!isTownValid(invalidTown1));
    assert(!isTownValid(invalidTown2));
    assert(isAddressValid(validAddress1, validTown));
    assert(!isAddressValid(invalidAddress1, validTown));

    assert(distance(validAddress1, validAddress1, validTown) == 0);
    std::size_t result = distance(validAddress1, validAddress2, validTown);
    std::cout << "Distance between addresses: " << result << std::endl;
    //assert(distance(validAddress1, validAddress2, validTown) == 19);
}
