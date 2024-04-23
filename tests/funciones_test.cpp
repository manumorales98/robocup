#include "funciones.h"
#include <gtest/gtest.h>

TEST(getPlayer, getPlayerOK)
{
  string mensaje = "(init r 1 before_kick_off)";
  Player miPlayer = getPlayer(mensaje);
  EXPECT_EQ(miPlayer.dorsal, "1");
  EXPECT_EQ(miPlayer.lado_campo, "r");
}