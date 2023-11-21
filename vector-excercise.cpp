#include <cassert>
#include <iostream>
#include <vector>

using Box = int;
using Stack = std::vector<Box>;
using Storage = std::vector<Stack>;

struct Move {
    std::size_t from;
    std::size_t to;
};

using Instructions = std::vector<Move>;

/*
 * Nastoupili jste jako programátor do firmy, která se zabývá výrobou chytrých jeřábů.
 * Dostali jste za úkol vytvořit simulátor jeřábu, který bude schopen přesouvat krabice z jedho sloupce na druhý.
 * Vždy můžete přesunout pouze jednu krabici a to tak, že vezmete krabici z vrcholu jednoho sloupce a přesunete ji na vrchol druhého sloupce.
 *
 * 1. Napište funkci show, která vypíše obsah skladiště na standardní výstup.
 *    A to ve formátu:
 *
 *        [4]    
 *    [2] [3]    
 *    [0] [1] [5]
 *     0   1   2
 *
 * 2. Napište funkci move, která dostane jeden pokyn typu Move a skladiště typu Storage a provede přesun krabice.
 * 3. Napište overload funkce move, která dostane pokyny typu Instructions a skladiště typu Storage a provede všechny přesuny.
 */

void show(const Storage& storage) {
    for (int i = storage[0].size() - 1; i >= 0; i--) {
        for (const Stack& stack : storage) {
            if (i < static_cast<int>(stack.size())) {
                std::cout << "[" << stack[i] << "] ";
            } else {
                std::cout << "    "; // 4 spaces
            }
        }
        std::cout << std::endl;
    }
    for (u_int64_t i = 0; i < storage.size(); i++) {
        std::cout << " " << (i) << "  ";
    }
    std::cout << std::endl;
}

void move(const Move& move, Storage& storage) {
    storage[move.to].push_back(storage[move.from].back());
    storage[move.from].pop_back();
}

void move(const Instructions& instructions, Storage& storage) {
    for (u_int64_t i = 0; i < instructions.size(); i++) {
        move(instructions[i], storage);
        show(storage);
    }
}

int main() {
    Storage storage = {
        { 0, 1, 2, 3, 4, 5 },
        {},
        {}
    };

    Instructions instructions = {
        { 0, 1 },
        { 0, 2 },
        { 1, 2 },
        { 0, 1 },
        { 2, 0 },
        { 2, 1 },
        { 0, 1 },
    };

    show(storage);
    move(instructions, storage);
    // show(storage);

    return 0;
}
