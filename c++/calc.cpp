#include <iostream>
using namespace std;

int main()
{
    float num1;
    float num2;
    char operador;
    float resultado;

    cout << "Di un número: ";
    cin >> num1;
    cout << "Di un operador: ";
    cin >> operador;
    cout << "Di otro número: ";
    cin >> num2;
    
    switch (operador)
    {
    case '+':
        resultado = num1 + num2;
        break;
    case '-':
        resultado = num1 - num2;
        break;
    case '*':
        resultado = num1 * num2;
        break;
    case '/':
        if (num2 != 0)
        {
            resultado = num1 / num2;
        }
        else
        {
            cout << "No se puede dividir entre 0 ";
            return 1;
        }
        break;
    default:
        cout << "No es válido ";
        return 1;
    }

    

    cout << "El resultado es: " << resultado << endl;

    return 0;
}