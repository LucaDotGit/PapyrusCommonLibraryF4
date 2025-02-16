Scriptname System:Enumerable Hidden

;/
	Provides a fluent API for queueing of immutable arrays,
	heavily inspired by LINQ from C#.
/;

Var[] _source

Enumerable Function Empty() Global
	return From(none)
EndFunction

Enumerable Function From(Var[] akSource) Global
	Enumerable enumerable = System:ScriptObject.Create("System:Enumerable") as Enumerable
	enumerable.Constructor(akSource)
	return enumerable
EndFunction

Enumerable Function Range(int aiStart, int aiCount, int aiStep = 1) Global
	int[] values = System:Array.Range(aiStart, aiCount, aiStep)
	return From(values as Var[])
EndFunction

Enumerable Function RangeFloat(float afStart, int aiCount, float afStep = 1.0) Global
	float[] values = System:Array.RangeFloat(afStart, aiCount, afStep)
	return From(values as Var[])
EndFunction

Enumerable Function Repeat(int aiCount, Var akValue) Global
	Var[] values = System:Array.RepeatVar(aiCount, akValue)
	return From(values)
EndFunction

Function Constructor(Var[] akSource)
	_source = akSource
EndFunction

Enumerable Function Copy()
	Var[] values = System:Array.Copy(_source)
	return From(values)
EndFunction

Enumerable Function DeepCopy()
	Var[] values = System:Array.DeepCopy(_source)
	return From(values)
EndFunction

Var[] Function ToArray()
	return System:Array.Copy(_source)
EndFunction


bool Function IsEmpty()
	return System:Array.IsEmpty(_source)
EndFunction

bool Function Contains(Var akValue)
	return System:Array.Contains(_source, akValue)
EndFunction

bool Function StartsWith(Var akValue)
	return System:Array.StartsWith(_source, akValue)
EndFunction

bool Function EndsWith(Var akValue)
	return System:Array.EndsWith(_source, akValue)
EndFunction

int Function Count()
	return System:Array.Count(_source)
EndFunction

Var Function First()
	return System:Array.First(_source)
EndFunction

Var Function Last()
	return System:Array.Last(_source)
EndFunction

Var Function Find(Var akValue)
	return System:Array.Find(_source, akValue)
EndFunction

Var Function FindLast(Var akValue)
	return System:Array.FindLast(_source, akValue)
EndFunction

bool Function Any(Var[] akArray)
	return System:Array.Any(_source, akArray)
EndFunction

bool Function All(Var[] akArray)
	return System:Array.All(_source, akArray)
EndFunction

Var Function Min()
	return System:Array.Min(_source)
EndFunction

Var Function Max()
	return System:Array.Max(_source)
EndFunction

int Function Sum()
	int[] numbers = _source as int[]
	If (!numbers)
		System:Internal.LogError("The source is not an int array")
		return 0
	EndIf

	return System:Array.Sum(numbers)
EndFunction

float Function SumFloat()
	float[] numbers = _source as float[]
	If (!numbers)
		System:Internal.LogError("The source is not a float array")
		return 0.0
	EndIf

	return System:Array.SumFloat(numbers)
EndFunction

int Function Average()
	int[] numbers = _source as int[]
	If (!numbers)
		System:Internal.LogError("The source is not an int array")
		return 0
	EndIf

	return System:Array.Average(numbers)
EndFunction

float Function AverageFloat()
	float[] numbers = _source as float[]
	If (!numbers)
		System:Internal.LogError("The source is not a float array")
		return 0.0
	EndIf

	return System:Array.AverageFloat(numbers)
EndFunction

Enumerable Function Union(Var[] akArray)
	Var[] values = System:Array.Union(_source, akArray)
	return self
EndFunction

Enumerable Function Intersect(Var[] akArray)
	Var[] values = System:Array.Intersect(_source, akArray)
	return self
EndFunction

Enumerable Function Except(Var[] akArray)
	Var[] values = System:Array.Except(_source, akArray)
	return self
EndFunction

Enumerable Function Take(int aiCount)
	Var[] values = System:Array.Take(_source, aiCount)
	return self
EndFunction

Enumerable Function Skip(int aiCount)
	Var[] values = System:Array.Skip(_source, aiCount)
	return self
EndFunction

Enumerable Function Distinct()
	Var[] values = System:Array.Distinct(_source)
	return self
EndFunction

Enumerable Function Order()
	Var[] values = System:Array.Sort(_source)
	return self
EndFunction

Enumerable Function OrderDescending()
	Var[] values = System:Array.Sort(_source, abDescending = true)
	return self
EndFunction

Enumerable Function Shuffle()
	Var[] values = System:Math.Shuffle(_source)
	return self
EndFunction

Enumerable Function Reverse()
	Var[] values = System:Array.Reverse(_source)
	return self
EndFunction

string Function Join(string asSeparator = ", ")
	return System:Array.Join(_source, asSeparator)
EndFunction

Enumerable Function Append(Var akValue)
	Var[] values = System:Array.Add(_source, akValue)
	return self
EndFunction

Enumerable Function AppendRange(Var[] akArray)
	Var[] values = System:Array.AddRange(_source, akArray)
	return self
EndFunction

Enumerable Function Prepend(Var akValue)
	Var[] values = System:Array.Insert(_source, 0, akValue)
	return self
EndFunction

Enumerable Function PrependRange(Var[] akArray)
	Var[] values = System:Array.InsertRange(_source, 0, akArray)
	return self
EndFunction

Enumerable Function Remove(Var akValue)
	Var[] values = System:Array.Remove(_source, akValue)
	return self
EndFunction

Enumerable Function RemoveAll(Var akValue)
	Var[] values = System:Array.RemoveAll(_source, akValue)
	return self
EndFunction
