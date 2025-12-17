## MATH INTERPRETER
---

Este projeto consiste em um **interpretador matemático de expressões em forma de string**, desenvolvido em **C++**.

### Funcionamento geral

O interpretador executa as seguintes etapas:

- Coleta a entrada do usuário na forma de uma *string* contendo uma expressão matemática;

- Realiza a **tokenização** da expressão, convertendo-a em *tokens* classificados como:
  - **Números**, armazenados em variáveis do tipo `double`;
  - **Operadores**, armazenados em variáveis do tipo `char`;

- Verifica a **validade sintática** da expressão tokenizada;

- Insere os *tokens* válidos em uma **fila (queue)**;

- Converte a sequência de *tokens* da **notação infixa** para a **notação posfixa**;

- Constrói uma **árvore binária de expressão** a partir da notação posfixa;

- Percorre a árvore binária para **interpretar a expressão** e retornar o **resultado matemático final**.

---

### Observações

A arquitetura do projeto prioriza a **modularização**, permitindo uma separação clara entre as etapas de tokenização, validação, conversão de notações e avaliação da expressão, o que facilita a manutenção e a expansão futura do interpretador.
