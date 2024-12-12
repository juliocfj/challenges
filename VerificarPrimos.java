
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class VerificarPrimos {
    // Método para verificar se um número é primo
    public static boolean verificarPrimo(int numero) {
        if (numero <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(numero); i++) {
            if (numero % i == 0) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Obter intervalo dos números a serem gerados aleatoriamente
        System.out.print("Digite o início do intervalo para os números aleatórios: ");
        int inicioIntervalo = scanner.nextInt();
        System.out.print("Digite o fim do intervalo para os números aleatórios: ");
        int fimIntervalo = scanner.nextInt();

        // Gerar lista de números inteiros aleatórios dentro do intervalo especificado
        Random random = new Random();
        List<Integer> listaNumeros = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            listaNumeros.add(random.nextInt(fimIntervalo - inicioIntervalo + 1) + inicioIntervalo);
        }

        // Filtrar e exibir números primos
        List<Integer> numerosPrimos = new ArrayList<>();
        for (int num : listaNumeros) {
            if (verificarPrimo(num)) {
                numerosPrimos.add(num);
            }
        }

        System.out.println("Lista de números aleatórios: " + listaNumeros);
        System.out.println("Números primos na lista: " + numerosPrimos);
        
        scanner.close();
    }
}
