
def calculadora():
    print("===== CALCULADORA =====")
    print("1 - Adição (+)")
    print("2 - Subtração (-)")
    print("3 - Multiplicação (*)")
    print("4 - Divisão (/)")
    print("0 - Sair")

    while True:
        opcao = input("\nEscolha uma operação: ")

        if opcao == "0":
            print("Calculadora encerrada!")
            break

        if opcao not in ["1", "2", "3", "4"]:
            print("Opção inválida!")
            continue

        numero1 = float(input("Digite o primeiro número: "))
        numero2 = float(input("Digite o segundo número: "))

        if opcao == "1":
            resultado = numero1 + numero2

        elif opcao == "2":
            resultado = numero1 - numero2

        elif opcao == "3":
            resultado = numero1 * numero2

        elif opcao == "4":
            if numero2 == 0:
                print("Erro: divisão por zero!")
                continue
            resultado = numero1 / numero2

        print(f"Resultado: {resultado}")


calculadora()
