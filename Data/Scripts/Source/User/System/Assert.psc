Scriptname System:Assert Const Hidden Native BetaOnly

;/
	Provides common assertion functions for debugging purposes.
/;

Function IsTrue(bool abCondition, string asMessage = "") Global Native BetaOnly
Function IsFalse(bool abCondition, string asMessage = "") Global Native BetaOnly

Function IsNone(Var akValue, string asMessage = "") Global Native BetaOnly
Function NotNone(Var akValue, string asMessage = "") Global Native BetaOnly

Function Equals(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly
Function NotEquals(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly

Function IsLessThan(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly
Function IsLessThanOrEqual(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly
Function IsGreaterThan(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly
Function IsGreaterThanOrEqual(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly

Function IsInRange(Var akValue, Var akMin, Var akMax, string asMessage = "") Global Native BetaOnly
Function NotInRange(Var akValue, Var akMin, Var akMax, string asMessage = "") Global Native BetaOnly

Function RefEquals(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly
Function RefNotEquals(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly

Function TypeEquals(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly
Function TypeNotEquals(Var akLeft, Var akRight, string asMessage = "") Global Native BetaOnly
