#include <a_samp>
#include <binary>
#include <DOF2>


main(){}

public OnGameModeInit()
{
	printf("=== BENCHMARK DOF2 vs BINARY.INC ===");
	
	TestarDOF2();
	TestarBinary();
	TestarBinary_NOOPEN();
	
	return 1;
}

stock TestarDOF2()
{
	new tempo[2], tentat[10], media;
	
	// Teste escrita DOF2
	media = 0;
	for(new t = 0; t < 10; t++)
	{
		tempo[0] = GetTickCount();
		for(new i = 0; i < 100; i++)
		{
			DOF2::SetString("bench_dof2.txt", "key1", "valor");
			DOF2::SetString("bench_dof2.txt", "key2", "valor");
			DOF2::SetString("bench_dof2.txt", "key3", "valor");
			DOF2::SetString("bench_dof2.txt", "key4", "valor");
			DOF2::SetString("bench_dof2.txt", "key5", "valor");
			DOF2::SaveFile();
		}
		tempo[1] = GetTickCount();
		tentat[t] = tempo[1] - tempo[0];
	}
	for(new i = 0; i < 10; i++) media += tentat[i];
	printf("DOF2 Escrita: %ims", media / 10);
	
	// Teste leitura DOF2
	media = 0;
	for(new t = 0; t < 10; t++)
	{
		tempo[0] = GetTickCount();
		for(new i = 0; i < 100; i++)
		{
			DOF2::GetString("bench_dof2.txt", "key1");
			DOF2::GetString("bench_dof2.txt", "key2");
			DOF2::GetString("bench_dof2.txt", "key3");
			DOF2::GetString("bench_dof2.txt", "key4");
			DOF2::GetString("bench_dof2.txt", "key5");
		}
		tempo[1] = GetTickCount();
		tentat[t] = tempo[1] - tempo[0];
	}
	for(new i = 0; i < 10; i++) media += tentat[i];
	printf("DOF2 Leitura: %ims", media / 10);
}

stock TestarBinary()
{
	new tempo[2], tentat[10], media;
	
	// Teste escrita Binary
	media = 0;
	BIN::Open("bench_binary.bin");
	for(new t = 0; t < 10; t++)
	{
		tempo[0] = GetTickCount();
		for(new i = 0; i < 100; i++)
		{
			BIN::WriteString("key1", "valor");
			BIN::WriteString("key2", "valor");
			BIN::WriteString("key3", "valor");
			BIN::WriteString("key4", "valor");
			BIN::WriteString("key5", "valor");
			BIN::Save();
		}
		tempo[1] = GetTickCount();
		tentat[t] = tempo[1] - tempo[0];
	}
	for(new i = 0; i < 10; i++) media += tentat[i];
	printf("Binary Escrita: %ims", media / 10);
	
	// Teste leitura Binary
	media = 0;
	new val[32];
	for(new t = 0; t < 10; t++)
	{
		tempo[0] = GetTickCount();
		for(new i = 0; i < 100; i++)
		{
			BIN::Open("bench_binary.bin");
			BIN::GetKeyValueEx("key1", val, sizeof(val));
			BIN::GetKeyValueEx("key2", val, sizeof(val));
			BIN::GetKeyValueEx("key3", val, sizeof(val));
			BIN::GetKeyValueEx("key4", val, sizeof(val));
			BIN::GetKeyValueEx("key5", val, sizeof(val));
			BIN::Save();
		}
		tempo[1] = GetTickCount();
		tentat[t] = tempo[1] - tempo[0];
	}
	for(new i = 0; i < 10; i++) media += tentat[i];
	printf("Binary Leitura: %ims", media / 10);
}

stock TestarBinary_NOOPEN()
{
	new tempo[2], tentat[10], media;
	
	// Teste escrita Binary
	media = 0;
	BIN::Open("bench_binary.bin");
	for(new t = 0; t < 10; t++)
	{
		tempo[0] = GetTickCount();
		for(new i = 0; i < 100; i++)
		{
			BIN::WriteString("key1", "valor");
			BIN::WriteString("key2", "valor");
			BIN::WriteString("key3", "valor");
			BIN::WriteString("key4", "valor");
			BIN::WriteString("key5", "valor");
			BIN::Save();
		}
		tempo[1] = GetTickCount();
		tentat[t] = tempo[1] - tempo[0];
	}
	for(new i = 0; i < 10; i++) media += tentat[i];
	printf("Binary (Sem abrir direto) Escrita: %ims", media / 10);
	
	// Teste leitura Binary
	media = 0;
	new val[32];
	BIN::Open("bench_binary.bin");
	for(new t = 0; t < 10; t++)
	{
		tempo[0] = GetTickCount();
		for(new i = 0; i < 100; i++)
		{
			BIN::GetKeyValueEx("key1", val, sizeof(val));
			BIN::GetKeyValueEx("key2", val, sizeof(val));
			BIN::GetKeyValueEx("key3", val, sizeof(val));
			BIN::GetKeyValueEx("key4", val, sizeof(val));
			BIN::GetKeyValueEx("key5", val, sizeof(val));
			BIN::Save();
		}
		tempo[1] = GetTickCount();
		tentat[t] = tempo[1] - tempo[0];
	}
	for(new i = 0; i < 10; i++) media += tentat[i];
	printf("Binary (Sem abrir direto) Leitura: %ims", media / 10);
}
