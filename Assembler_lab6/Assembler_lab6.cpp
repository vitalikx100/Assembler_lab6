#include <iostream>
#include <cmath>

using namespace std;

int main()
{
  double a, b, x;
  double c1 = 1.0;
  double c3 = 3.0;
  double c6 = 6.0;
  int error = 0;

  cout << "Input a, b: ";
  cin >> a >> b;
  _asm
  {
    finit;
    fld a; st(0) = a
    fld b; st(0) = b; st(1) = a
    fcomip st, st(1); st(0) = a
    jb great; если a > b, переход на метку great
    ja m4; если a < b, переход на метку m4
    je equ;

    great:
      fld c1; st(0) = 1
      fld a; st(0) = a;
      fmul a; st(0) = a ^ 2;
      fsub b; st(0) = a ^ 2 - b;
      fld a; st(0) = a; st(1) = a ^ 2 - b
      fsub c3; st(0) = a - 3; st(1) = a ^ 2 - b
      fldz; st(1) = 0; st(1) = a - 3; st(2) = a ^ 2 - b
      fcomip st, st(1); st(0) = a - 3; st(1) = a ^ 2 - b
      jz error_0;
      fdivp st(1), st;

      fstp x;
      
      jmp end_if;

    m4:
      fld c1; st(0) = 1
      fld a; st(0) = a; 
      fmul a; st(0) = a ^ 2; 
      fsub c3; st(0) = a ^ 2 - 3
      fld b; st(0) = b; st(1) = a ^ 2 - 3
      fldz;
      fcomip st, st(1);
      jz error_0;
      fdivp st(1), st; st(0) = (a ^ 2 - 3) / b

      fstp x;

      jmp end_if

    equ:
      fld c6; st(0) = 6
      fstp x;
      jmp end_if;

    test AX, 1
    jnz error_io

    jmp end_if

    error_0 :
        mov error, 1
        jmp end_if

    error_io :
        mov error, 2
        jmp end_if

    end_if:
      
  }
  if (error == 1) cout << "division by zero";
  if (error == 2) cout << "invalid opertation";
  if (error == 0)
  {
    cout << "asm: " << x << endl;
    if (a > b) cout << "C++: " << (double)((pow(a, 2) - b) / (a - 3));
    if (a < b) cout << "C++: " << (double)((pow(a, 2) - 3) / b);
    if (a == b) cout << "C++: " << 6;
  }
  
  return 0;
}