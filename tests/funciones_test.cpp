#include "funciones.h"
#include <gtest/gtest.h>

<<<<<<< HEAD
TEST(getPlayer, getPlayerOK)
{
  string mensaje = "(init r 1 before_kick_off)";
  Player miPlayer = getPlayer(mensaje);
  EXPECT_EQ(miPlayer.dorsal, "1");
  EXPECT_EQ(miPlayer.lado_campo, "r");
}
=======

// Test para comprobar que la estructura jugador se crea adecuadamente a partir del 1er mensaje del servidor
TEST(getPlayer, getPlayerOK)
{
  string mensaje1 = "(init r 1 before_kick_off)";
  Player miPlayer1 = getPlayer(mensaje1);
  EXPECT_EQ(miPlayer1.dorsal, "1");
  EXPECT_EQ(miPlayer1.lado_campo, "r");
  string mensaje2 = "(init l 10 before_kick_off)";
  Player miPlayer2 = getPlayer(mensaje2);
  EXPECT_EQ(miPlayer2.dorsal, "10");
  EXPECT_EQ(miPlayer2.lado_campo, "l");
}


// Test para comprobar el check_init con el mensaje bueno
TEST(checkInit, checkinitTRUE)
{
  string mensaje1 = "(hear 0 referee kick_off_l)";
  EXPECT_EQ(check_init(mensaje1), true);
}

>>>>>>> 9fad1ea (Tarea 2 (No chutan))
