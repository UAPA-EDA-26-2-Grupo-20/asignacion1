def main() -> None:
    # Matrices y arreglos
    stock: list[list[int]] = []
    distancia: list[list[int]] = []
    umbral: list[int] = [10 for _ in range(15)]

    # Contadores
    total_movimientos = 0
    costo_total = 0

    # Llenar stock (datos de prueba)
    for i in range(6):
        nueva: list[int] = []
        for _ in range(15):
            nueva.append(5 + i * 5)
        stock.append(nueva)

    # Llenar distancia
    for i in range(6):
        nueva: list[int] = []
        for j in range(6):
            nueva.append(abs(i - j) + 1)
        distancia.append(nueva)

    for i in range(15):
        for j in range(6):
            if not necesita(stock[j][i], umbral[i]):
                continue

            # Si necesita producto
            # Buscar quien tiene excedente
            for k in range(6):
                if excedente(stock[k][i], umbral[i]) <= 0:
                    continue

                falta = umbral[i] - stock[j][i]
                sobra = stock[k][i] - umbral[i]

                mover = min(falta, sobra)
                costo = mover * distancia[k][j]

                # Actualizar
                stock[j][i] += mover
                stock[k][i] -= mover

                total_movimientos += 1
                costo_total += costo

                # Mostrar producto
                print(f"Producto {i}: {mover} unidades movidas de almacen {k} a almacen {j}. Costo: {costo}")

                # Si ya no necestia más, salir
                if stock[j][i] >= umbral[i]:
                    break

    print("-----------------------")
    print(f"Total de movimientos: {total_movimientos}")
    print(f"Costo total: {costo_total}")
    

def necesita(cantidad: int, umbral: int) -> bool:
    return cantidad < umbral


def excedente(cantidad: int, umbral: int) -> int:
    if cantidad > umbral:
        return cantidad - umbral
    return 0


if __name__ == "__main__":
    main()
