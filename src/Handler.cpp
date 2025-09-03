#include "../include/Handler.hpp"
using namespace std;
using namespace sf;

void Handler::handle_resize (const Event::Resized& resized, RenderWindow& window, Vector2u& last_window_size)
{   
    // Get the new size of the window
    Vector2u ws = resized.size;

    if(ws.x == last_window_size.x && ws.y == last_window_size.y)
        return; // if the size is the same as the last size, do nothing

    // if the new size is smaller than the minimum size, set it to the minimum size (same for maximum size)
    if(ws.x < MIN_SCREEN_WIDTH || ws.y < MIN_SCREEN_HEIGHT)
        window.setSize({MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT});
    else if(ws.x > MAX_SCREEN_WIDTH || ws.y > MAX_SCREEN_HEIGHT)
        window.setSize({MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT});
    else
        resizeWindow(ws, last_window_size, window);
}


void Handler::resizeWindow(Vector2u& ws, Vector2u &last_window_size, RenderWindow &window)
{
        // casting to float
        float x_float = static_cast<float>(ws.x);
        float y_float = static_cast<float>(ws.y);
        
        // calculate the new aspect ratio 
        float new_aspect = x_float/y_float;

        // adjust the size of the window to maintain the aspect ratio 1.5
        (new_aspect < ASPECT) ? ws = {ws.x,static_cast<unsigned>(ws.x/ASPECT)} : ws = {static_cast<unsigned>(ws.y*ASPECT),ws.y};

        // set the last size of the window to the new size
        last_window_size = {ws.x, ws.y};

        // set the new size of the window
        window.setSize(ws);
}


void Handler::handle(const Event::KeyPressed& key, GameState& game_state)
{
    // Handle key pressed events
    switch (key.code)
    {
        case Keyboard::Key::Escape:
            if(auto state = dynamic_cast<PausedState*>(game_state.state.get())) {
                state->resume();
                game_state.state = move(make_unique<RunningState>(game_state));
            }
            else if(dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.state = move(make_unique<PausedState>(game_state));
            break;

        case Keyboard::Key::Enter:

            handleEnterPressed(game_state); // Handle enter key events
            break;

        case Keyboard::Key::P:
            if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.player.isAttacking = true;
            break;

        case Keyboard::Key::Up:
            if(DialogState* dialogState = dynamic_cast<DialogState*>(game_state.state.get()))
            {
                dialogState->setAnswer();
            }
            break;

        case Keyboard::Key::Down:
            if(DialogState* dialogState = dynamic_cast<DialogState*>(game_state.state.get()))
            {
                dialogState->setAnswer();
            }
            break;

        case Keyboard::Key::W:
                if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                    game_state.move_directions[UP] = true;
            break;

        case Keyboard::Key::S:
            if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.move_directions[DOWN] = true;
            break;

        case Keyboard::Key::A:
            if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.move_directions[LEFT] = true;
            break;

        case Keyboard::Key::D:
            if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.move_directions[RIGHT] = true;
            break;

        case Keyboard::Key::F:
            if(auto state = dynamic_cast<PausedState*>(game_state.state.get())) {
                if(!game_state.tilemap->isFightable()) {
                    game_state.changeMap("assets/maps/arena.png", "assets/maps/arena.csv", 2, true);
                    state->resume();
                    game_state.state = move(make_unique<RunningState>(game_state));
                }
            }
            break;
        
        case Keyboard::Key::H:
            if(auto state = dynamic_cast<PausedState*>(game_state.state.get())) {
                if(game_state.tilemap->isFightable()) {
                    game_state.changeMap("assets/maps/main.png", "assets/maps/main.csv", 8, false);
                    state->resume();
                    game_state.state = move(make_unique<RunningState>(game_state));
                }
            }
            break;
                
    }
}

void Handler::handleEnterPressed(GameState& game_state)
{
    // Startstate -> RunningState
    if(dynamic_cast<StartState*>(game_state.state.get()))
        game_state.state = move(make_unique<RunningState>(game_state));


    // RunningState -> DialogState
    else if(dynamic_cast<RunningState*>(game_state.state.get()))
    {
        // If the player is in dialogue with an NPC, print the dialogue to the console
        if(game_state.player.dialogueActive)
        {
            Npc& npc = dynamic_cast<Npc&>(*game_state.player.currentNpc);
            game_state.state = move(make_unique<DialogState>(game_state, npc));
        }
    }

    // DialogState -> RunningState
    else if(DialogState* dialogState = dynamic_cast<DialogState*>(game_state.state.get()))
    {
        // If the current NPC is not in dialogue, switch back to the running state
        if(!dialogState->getCurrentNpc().isInDialogue())
        {
            game_state.player.dialogueActive = false;
            game_state.player.currentNpc = nullptr;
            game_state.state = move(make_unique<RunningState>(game_state));
        } else {
            dialogState->advanceDialogue();
        }
        for(auto& directions : game_state.move_directions)
            directions = false;
    }
}

void Handler::handle(const Event::KeyReleased& key, GameState& game_state)
{
    // Handle key released events
    switch (key.code)
    {
        case Keyboard::Key::P:
            if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.player.isAttacking = false;
            break;
        case Keyboard::Key::W:
            if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.move_directions[UP] = false;
            break;

        case Keyboard::Key::S:
            if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.move_directions[DOWN] = false;
            break;

        case Keyboard::Key::A:
            if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.move_directions[LEFT] = false;
            break;

        case Keyboard::Key::D:
            if(RunningState* runningState = dynamic_cast<RunningState*>(game_state.state.get()))
                game_state.move_directions[RIGHT] = false;
            break;
    }
}