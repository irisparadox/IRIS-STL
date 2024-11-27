#include <vector.h>
#include <vector>
#include <pair.h>
#include <utility>
#include <string>
#include <iostream>
#include <hash.h>
#include <list>
#include <list.h>
#include <unordered_map.h>
#include <unordered_map>

int main() {
	{
		iris::unordered_map<int, int> map;
		map.insert({ 1, 2 });
		map.insert({ 2, 2 });
		map.insert({ 5, 10 });
		map.insert({ 24, 1 });
		map.insert({ 643, 10 });
		map.insert({ 1024, 8 });
	}
	{
		iris::list<int> list = { 1, 2, 3 };
		for (auto val : list) {
			std::cout << val << '\n';
		}
	}
	{
		iris::vector<std::string> testCases = {
		"hola", "mundo", "amor", "familia", "trabajo", "felicidad", "pasi�n", "amistad", "comida", "salud",
		"paz", "cielo", "mar", "tiempo", "libertad", "futuro", "noche", "d�a", "nieve", "luz",
		"agua", "tierra", "fuego", "aire", "viento", "coraz�n", "estudio", "tecnolog�a", "desarrollo",
		"aprendizaje", "sabidur�a", "espejo", "flor", "�rbol", "monta�a", "r�o", "sendero", "camino",
		"verdad", "mentira", "conocimiento", "educaci�n", "lengua", "literatura", "cultura", "m�sica",
		"pintura", "ciencia", "historia", "sociedad", "persona", "hombre", "mujer", "ni�o", "adolescente",
		"adulto", "viejo", "joven", "viaje", "vacaciones", "ciudad", "pueblo", "campo", "natura",
		"paisaje", "pintura", "cultura", "pa�s", "gente", "pueblo", "realidad", "fantas�a", "sue�o",
		"justicia", "legalidad", "violencia", "guerra", "paz", "revoluci�n", "cambio", "progreso",
		"comunicaci�n", "televisi�n", "internet", "redes", "inform�tica", "salud", "medicina",
		"alimento", "higiene", "salud", "ejercicio", "deporte", "arte", "fotograf�a", "dibujo",
		"pintura", "escultura", "danza", "cine", "teatro", "espect�culo", "entretenimiento",
		"est�tica", "ciencia", "f�sica", "matem�ticas", "qu�mica", "biolog�a", "geograf�a", "astronom�a",
		"ecolog�a", "evoluci�n", "genes", "c�lula", "sangre", "m�dico", "hospital", "enfermero",
		"hospital", "operaci�n", "medicamento", "cura", "enfermedad", "salud", "cuerpo", "mente",
		"psicolog�a", "sociedad", "pol�tica", "derechos", "justicia", "gobierno", "ley", "reforma",
		"democracia", "dictadura", "monarqu�a", "revoluci�n", "congreso", "presidente", "ciudadano",
		"voto", "elecci�n", "partido", "socialismo", "capitalismo", "comunismo", "liberalismo",
		"anarquismo", "feminismo", "racismo", "sexismo", "homofobia", "tolerancia", "respeto",
		"igualdad", "solidaridad", "ayuda", "cooperaci�n", "compa�erismo", "hermandad", "trabajo",
		"econom�a", "empleo", "dinero", "desempleo", "salario", "ricos", "pobres", "acuerdo",
		"mercado", "comercio", "empresa", "industria", "trabajador", "empleado", "empleador",
		"trabajo", "sueldo", "ahorro", "crisis", "crecimiento", "competencia", "gasto", "gobierno",
		"presupuesto", "impuestos", "subsidio", "empleabilidad", "progreso", "futuro", "destino",
		"camino", "esfuerzo", "motivaci�n", "superaci�n", "�xito", "fracaso", "depresi�n", "ansiedad",
		"estr�s", "alegr�a", "tristeza", "felicidad", "sufrimiento", "emoci�n", "sentimiento",
		"pensamiento", "raz�n", "mente", "alma", "cuerpo", "psique", "respiraci�n", "vivir", "morir"
		};

		std::unordered_map<unsigned long long, int> hashmap;
		int collisions = 0;

		for (const auto val : testCases) {
			unsigned long long hashedValue = iris::XXH64(val);

			if (hashmap.count(hashedValue)) ++collisions;

			++hashmap[hashedValue];
		}
	}
	{
		iris::list<iris::list<int>> lists;
		iris::list<int> list = { 1, 2, 3 };

		lists.push_back(list);

		list.pop_back();

		long long hash = iris::XXH64(list);
	}
	{
		std::list<std::vector<int>> stdListVec;
		std::vector<int> stdvec = { 1, 2, 3 };
		stdvec.push_back(4);
		stdvec.push_back(5);

		stdListVec.push_front(stdvec);
	}
	{
		iris::vector<int> vec;
		vec.push_back(16);
		vec.push_back(32);
		vec.push_back(64);
		vec.push_back(128);
		vec.push_back(256);
		vec.push_back(512);
		vec.push_back(1024);

		iris::vector<bool> vec2;
		vec2.push_back(true);
		vec2.push_back(true);
		vec2.push_back(false);
		vec2.push_back(true);
		vec2.push_back(false);
		vec2.push_back(false);
		vec2.push_back(true);

		iris::pair<int, int> _Mypair(1, 2);
		iris::pair<int, int> _Mypair2(1, 2);

		bool is = (_Mypair == _Mypair2);

		std::cout << vec.front() << '\n';

		std::cout << vec[5] << '\n';

		vec.pop_back();

		iris::vector<int>::iterator it = vec.begin();

		it++;

		iris::vector<const char*> vec3(10, "abc");

		iris::list<int> list;
		iris::list<iris::vector<int>> listVec;

		list.push_back(5);
		list.push_front(10);
		list.push_back(20);
		list.push_front(30);

		listVec.push_front(vec);
		
		list.front();
		list.back();

		iris::vector<int> movevec(iris::move(vec));

		vec.push_back(10);
	}
	{
		int inputInt = 42;
		long long hashInt = iris::XXH64(inputInt);
		int input2 = 43;
		long long hashInt1 = iris::XXH64(input2);

		if (hashInt == hashInt1) return -1;
	}
	return 0;
}