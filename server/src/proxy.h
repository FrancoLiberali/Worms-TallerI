#include "socket.h"
#include "queue.h"
#include <string>
#include <vector>
#include <map>
#include <mutex>

#ifndef __PROXY_H__
#define __PROXY_H__

class Proxy{
	private:
		Socket socket;
		int id = 0;
		Queue* queue;
		Queue* prev_queue;
		std::mutex queue_mutex;
		
		// Recibe del socket un informacion de tamanio tam
		// que corresponde al largo de evento event
		// y luego lo encola en la cola actual.
		void receiveEventInfo(char event, int tam);
		
		// Encola en la cola actual el evento correspondiente
		// a la desconeccion del client con el que este proxy
		// establecia comunicacion.
		void pushDisconnectionMessage();
	public:
		// Objeto que establece protocolo de comunicacion con un jugador via 
		// el socket recibido.
		// La estructura de los mensajes respeta el protocolo
		// de comunicacion definido para este programa.
		// Los mensajes recibidos seran encolados en la cola queue.
		Proxy(Socket socket_e, Queue* queue);
		
		~Proxy() noexcept;
		
		// Cierra la comunicion del socket con el cliente.
		void closeCommunication();
		
		// Agrega una nueva queue, para encolar los mensajes en ella.
		// Guarda una referencia a la queue anterior en prev_queue
		void addNewQueue(Queue* queue);
		
		// Vuelve atras el cambio de queue, haciendo que la queue
		// a la que se encolan los mensajes recibidos sea la anterior.
		void changeToPrevQueue();
		
		// Recive el nombre de un jugador
		// Ese nombre se devuelve en lugar de ser encolado.
		const std::string receiveName();
		
		// Recibe un char del socket y determina a partir de el
		// que mensaje significa y recibe el mensaje del tamanio que corresponde
		// para luego encolarlo.
		void receiveEvent();
		
		// Lleva a cabo las acciones para que cuando el client este dentro de una
		// partida y se desconecte, el hall sepa que este client se desconecto
		void disconnect();
		
		// Recibe un char del socket.
		const unsigned char receiveChar();
		
		// Envia a un jugador su numero de id y lo guarda en id.
		void sendPlayerId(const int id);
		
		// Envia al jugador el nombre del archivo del fondo
		// de pantalla que tiene el mapa que esta por jugar.
		void sendMapBackground(const std::string& background);
		
		// Avisa al jugador que un viga fue creada en la posicion x,y
		// con un angulo angle
		void sendVigaCreation(int x, int y, int angle);
		
		// Avisa al jugador las dimensiones del mapa a dibujar.
		void sendMapDimentions(int widht, int height);
		
		// Avisa al jugador que un gusano de gusano_id, cuyo duenio es player_id
		// fue creado en la posicion x,y con una direccion direction y un angulo angle.
		void sendGusanoCreation(int gusano_id, int player_id, int x, int y, int direction, int angle);
		
		// Avisa que comenzo un nuevo turno donde juga el jugador player_id,
		// y realiza accione sobre el gusano gusano_id
		void sendTurnBegining(int player_id, int gusano_id);
		
		// Avisa el cambio de posicion de un gusano gusano_id a la posicion
		// x,y con una direccion direction y una angulo angle.
		void sendGusanoPosition(int gusano_id, int x, int y, int direction, int angle);
		
		// Avisa que el gusano gusano_id cambio de estado al estado new_state.
		// Los estados pueden ser: en movimiento, en el aire, muerto y alcanzado por
		// un explosion.
		void sendStateChange(int gusano_id, int new_state);
		
		// Avisa de la creacion de un proyectil con un id proyectil_number,
		// que es del tipo de arma weapon
		void sendProjectileCreation(int projectile_number, int weapon, int direction, int x, int y, int angle);
		
		// Avisa el cambio de posicion del proyectil projectile_number		
		void sendProjectilePosition(int projectile_number, int x, int y, int angle);
		
		// Avisa la explosion del proyectil projectile_number
		void sendProjectileExplosion(int projectile_number);
		
		// Avisa que el gusano del turno actual saco un arma weapon
		void sendTakeWeapon(int weapon);
		
		// Avisa que el gusano del turno actual cambio el angulo de apuntado
		// siendo change -1 si el angulo se redujo o 1 si el angulo aumento
		// en el cambio minimo de angulo posible que son 5.625 grados
		void sendChangeSightAngle(int change);
		
		// Avisa que el gusano gusano_id cambio su vida a new_life
		void sendLifeChange(int gusano_id, int new_life);
		
		// Avisa la desconeccion de uno de los jugadores.
		// Cuando un juegador se desconecta, todos sus gusanos son eliminados.
		void sendPlayerDisconnection(int player_id);
		
		// Avisa que un jugador perdio porque todos sus gusanos murieron.
		void sendPlayerLoose(int player_id);
		
		// Avisa que un jugador gano porque sus gusanos son los unicos que siguen 
		// en pie
		void sendGameWon(int player_id);
		
		// Envia al jugador el mensaje de aviso de que debe crear 
		// una nueva sala en la lista de salas. Esto puede ser 
		// por una sala ha sido creada por otro jugador
		// o porque este jugador acaba de incresar al hall y no posee informacion
		// de una sala que ya existia
		void sendRoomCreation(const int room_id, const std::string& name, const int cant_players, 
							  const int max_players, const std::string& map_name);
		
		// Avisa que la room room_id ha cambiado la cantidad de jugadores
		// que estan dentro de ella esperando que inicie la partida
		// ha cant_players
		void sendRoomPlayersChange(int room_id, int cant_players);
		
		// Envia al jugador el mensaje de aviso de que una sala
		// debe dejar de ser mostrada. Esto sucede cuando la sala
		// se completa y el jugador ya no se puede conectar o cuando 
		// sala queda vacia y se destruye.
		void sendRoomDeletion(int room_id);
		
		// Avisa a el juegador la coneccion de un jugador de id y nombre name
		// a la room en la que este se enncuentra.
		// Esto puede ser por que el jugador se encontraba en una room y alguien
		// nuevo se conecta o porque el jugador se conecta a una room
		// y debe recibir la informacion de los que ya estaban dentro
		void sendPlayerConnection(int id, const std::string& name);
		
		// Envia al jugador la lista de los nombres de los mapas disponibles
		// en el servidor
		void sendAvailableMaps(const std::vector<std::string>& maps);
		
		// Avisa al jugador que se le agoto la municion del arma
		// weapon_id
		void sendFinishedAmunnition(int weapon_id);
		
		// Avisa que la herramienta teledirigida que
		// el jugador intentaba utilizar funciono
		// ya que la posicion elegida para su uso era correcta
		void sendRemoteWork(int weapon_id);
		
		// Avisa al jugador que paso un segundo del turno actual.
		void sendSecond();
		
		// Avisa al jugador que el viento cambio a un nuevo valor wind
		void sendWindChange(int wind);
		
		// Envia un entero de 4 bytes big endian. 
		void sendInt(const int to_send);
		
		Proxy(Proxy&& other);
		
};

#endif
