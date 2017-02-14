#include <iostream>
#include <array>
#include <GL\glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"

#include "Map.h"
#include "Disease.h"
#include "Model.h"

int main(int argc, char **argv) {

    //Model m_sir("SIR");
	Model m_sir("SEIR");

    int pop_width = 500;
    int pop_height = 500;
    int time = 500;
    int num_seeds = 1;

    //Disease disease("seir test", 3, 5, 10, 3, 5);
    //Disease disease("sir", 3, 15, 10, 2, 2);
    //Disease disease("sir_small range", 3, 20, 10);
	Disease disease("H1N1", 3, 43, 10);

    Map map(pop_width, pop_height);

    m_sir.init_counters(map);

    map.random_seed(disease, num_seeds);

    //map.random_seed_immunity(10);

    Display display(pop_height, pop_width, "Disease Map");

    Vertex *v_map = new Vertex[pop_height * pop_width];

    Shader shader("./res/basicShader");
    Shader imunity_shader("./res/imunityMap");
    Shader num_infected_shader("./res/infectedMap");

    int loops = 0;

    while (!display.IsClosed()) {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_I]) {
            printf("<I> is pressed.\n");
            imunity_shader.Bind();
            for (int i = 0; i < pop_height; i++) {
                for (int j = 0; j < pop_width; j++) {
                    double x = ((double) i - (pop_height / 2)) / (pop_height / 2);
                    double y = ((double) j - (pop_width / 2)) / (pop_width / 2);
                    double z = (double) map.get_immune(i, j);
                    v_map[i * pop_width + j].set_vec(glm::vec3(x, y, z));
                }
            }
        } else if (state[SDL_SCANCODE_N]) {
            printf("<N> is pressed.\n");
            num_infected_shader.Bind();
            for (int i = 0; i < pop_height; i++) {
                for (int j = 0; j < pop_width; j++) {
                    double x = ((double) i - (pop_height / 2)) / (pop_height / 2);
                    double y = ((double) j - (pop_width / 2)) / (pop_width / 2);
                    double z = (double) map.get_num_infected(i, j);
                    v_map[i * pop_width + j].set_vec(glm::vec3(x, y, z));
                }
            }
        } else {
            shader.Bind();
            if (loops < time && !state[SDL_SCANCODE_P]) {
                std::cout << "Time: " << loops << std::endl;
                map = m_sir.take_step(disease, map);
                loops++;
            }
            for (int i = 0; i < pop_height; i++) {
                for (int j = 0; j < pop_width; j++) {
                    double x = ((double) i - (pop_height / 2)) / (pop_height / 2);
                    double y = ((double) j - (pop_width / 2)) / (pop_width / 2);
                    double z = (double) map.get_person_state(i, j);
                    v_map[i * pop_width + j].set_vec(glm::vec3(x, y, z));
                }
            }
        }

        Mesh mesh(v_map, pop_height * pop_width);
        mesh.Draw();

        display.Update();
    }
    m_sir.export_counters("test");
    //m_sir.print_counters();
    return 0;
}
