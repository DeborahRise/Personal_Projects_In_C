char *commands[MAX_INPUT_SIZE];
            char *token = strtok(gcmd, ";");
            int num_commands = 0;

            while (token != NULL && num_commands < MAX_INPUT_SIZE) {
                commands[num_commands] = token;
                token = strtok(NULL, ";");
                num_commands++;
            }

            // Execute each command
            for (int i = 0; i < num_commands; i++) {
                char *command = commands[i];
                // The rest of your code to execute and wait for the command goes here
                // You can use the code you already have for executing a single command
            }
