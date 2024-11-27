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
		"hola", "mundo", "amor", "familia", "trabajo", "felicidad", "pasión", "amistad", "comida", "salud",
		"paz", "cielo", "mar", "tiempo", "libertad", "futuro", "noche", "día", "nieve", "luz",
		"agua", "tierra", "fuego", "aire", "viento", "corazón", "estudio", "tecnología", "desarrollo",
		"aprendizaje", "sabiduría", "espejo", "flor", "árbol", "montaña", "río", "sendero", "camino",
		"verdad", "mentira", "conocimiento", "educación", "lengua", "literatura", "cultura", "música",
		"pintura", "ciencia", "historia", "sociedad", "persona", "hombre", "mujer", "niño", "adolescente",
		"adulto", "viejo", "joven", "viaje", "vacaciones", "ciudad", "pueblo", "campo", "natura",
		"paisaje", "pintura", "cultura", "país", "gente", "pueblo", "realidad", "fantasía", "sueño",
		"justicia", "legalidad", "violencia", "guerra", "paz", "revolución", "cambio", "progreso",
		"comunicación", "televisión", "internet", "redes", "informática", "salud", "medicina",
		"alimento", "higiene", "salud", "ejercicio", "deporte", "arte", "fotografía", "dibujo",
		"pintura", "escultura", "danza", "cine", "teatro", "espectáculo", "entretenimiento",
		"estética", "ciencia", "física", "matemáticas", "química", "biología", "geografía", "astronomía",
		"ecología", "evolución", "genes", "célula", "sangre", "médico", "hospital", "enfermero",
		"hospital", "operación", "medicamento", "cura", "enfermedad", "salud", "cuerpo", "mente",
		"psicología", "sociedad", "política", "derechos", "justicia", "gobierno", "ley", "reforma",
		"democracia", "dictadura", "monarquía", "revolución", "congreso", "presidente", "ciudadano",
		"voto", "elección", "partido", "socialismo", "capitalismo", "comunismo", "liberalismo",
		"anarquismo", "feminismo", "racismo", "sexismo", "homofobia", "tolerancia", "respeto",
		"igualdad", "solidaridad", "ayuda", "cooperación", "compañerismo", "hermandad", "trabajo",
		"economía", "empleo", "dinero", "desempleo", "salario", "ricos", "pobres", "acuerdo",
		"mercado", "comercio", "empresa", "industria", "trabajador", "empleado", "empleador",
		"trabajo", "sueldo", "ahorro", "crisis", "crecimiento", "competencia", "gasto", "gobierno",
		"presupuesto", "impuestos", "subsidio", "empleabilidad", "progreso", "futuro", "destino",
		"camino", "esfuerzo", "motivación", "superación", "éxito", "fracaso", "depresión", "ansiedad",
		"estrés", "alegría", "tristeza", "felicidad", "sufrimiento", "emoción", "sentimiento",
		"pensamiento", "razón", "mente", "alma", "cuerpo", "psique", "respiración", "vivir", "morir"
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