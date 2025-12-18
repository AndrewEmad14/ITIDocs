Boolean Logic as Arithmetic

Convention
False = 0, True = 1
Variables: x, y \in \{0,1\}

⸻

Basic Operators

NOT
\text{NOT } x = 1 - x

AND
x \land y = x \cdot y

OR
x \lor y = x + y - x\cdot y

XOR
x \oplus y = x + y - 2x\cdot y

⸻

Derived Operators

NAND
x \uparrow y = 1 - x\cdot y

NOR
x \downarrow y = 1 - (x + y - x\cdot y)

XNOR (Equivalence)
x \leftrightarrow y = 1 - (x + y - 2x\cdot y)

⸻

Implication

Implication (x → y)
x \to y = 1 - x + x\cdot y

Reverse Implication (y → x)
y \to x = 1 - y + x\cdot y

⸻

Constants

TRUE
1

FALSE
0

⸻

Key Notes
• All Boolean operations can be expressed using addition, subtraction, and multiplication.
• These formulas are valid when variables are restricted to \{0,1\}.
• Any Boolean function can be written as a polynomial (Boolean/Zhegalkin polynomial).

⸻

Minimal Building Blocks

Using only:
1, x, +, \cdot, -

you can construct every logical operator.
