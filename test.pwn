#include <a_samp>
#include <binary>
#include <DOF2>


main(){}


public OnGameModeInit()
{
	new total_start = GetTickCount();
	new times[6];
	
	// Teste 1
	times[0] = GetTickCount();
	BIN::Open("dados.bin");
	BIN::WriteString("creator", "mateus-bsod");
	printf("creator = %s", BIN::GetKeyValue("creator"));
	BIN::WriteString("creator", "mateus-delicia");
	printf("creator = %s", BIN::GetKeyValue("creator"));
	BIN::Save();
	times[0] = GetTickCount() - times[0];
	
	// Teste 2
	times[1] = GetTickCount();
	BIN::Open("dados.bin");
	printf("creator = %s", BIN::GetKeyValue("creator"));
	BIN::Save();
	times[1] = GetTickCount() - times[1];
	
	// Teste 3
	times[2] = GetTickCount();
	BIN::Open("dados.bin");
	BIN::WriteString("chico", "bento");
	BIN::WriteString("creator", "templeOS");
	BIN::WriteString("fuck", "seila");
	BIN::Save();
	times[2] = GetTickCount() - times[2];
	
	// Teste 4
	times[3] = GetTickCount();
	BIN::Open("dados.bin");
	printf("creator = %s", BIN::GetKeyValue("creator"));
	printf("chico = %s", BIN::GetKeyValue("chico"));
	printf("fuck = %s", BIN::GetKeyValue("fuck"));
	BIN::Save();
	times[3] = GetTickCount() - times[3];
	
	// Teste 5
	times[4] = GetTickCount();
	BIN::Open("dados.bin");
	BIN::WriteString("chico", "1.000");
	BIN::WriteString("creator", "3234");
	BIN::WriteString("fuck", "DNASKLDNKLASNDKLNAS");
	BIN::Save();
	times[4] = GetTickCount() - times[4];
	
	// Teste 6
	times[5] = GetTickCount();
	BIN::Open("dados.bin");
	printf("creator = %s", BIN::GetKeyValue("creator"));
	printf("chico = %s", BIN::GetKeyValue("chico"));
	printf("fuck = %s", BIN::GetKeyValue("fuck"));
	BIN::Save();
	times[5] = GetTickCount() - times[5];
	
	// Resultados
	printf("\n=== BENCHMARK BINARY.INC ===");
	printf("Teste 1: %d ms", times[0]);
	printf("Teste 2: %d ms", times[1]);
	printf("Teste 3: %d ms", times[2]); // maior
	printf("Teste 4: %d ms", times[3]);
	printf("Teste 5: %d ms", times[4]);
	printf("Teste 6: %d ms", times[5]); // maior
	printf("-------------------");
	printf("Média: %d ms", (times[0]+times[1]+times[2]+times[3]+times[4]+times[5])/6);
	printf("Total: %d ms", GetTickCount() - total_start);
	
	return 1;
}
