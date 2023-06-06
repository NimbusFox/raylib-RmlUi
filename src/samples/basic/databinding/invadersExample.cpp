#include "samples/basic/databinding/invadersExample.h"
#include "RmlUi/Core/DataModelHandle.h"

Rml::DataModelHandle modelHandle;

static constexpr int numInvaders = 12;
static constexpr double incomingInvadersRate = 50; // Per minute

struct Invader {
    Rml::String name;
    Rml::String sprite;
    Rml::Colourb color{ 255, 255, 255 };
    float max_health = 0;
    float charge_rate = 0;
    float health = 0;
    float charge = 0;
};

struct InvadersData {
    float health = 0;
    float charge = 0;
    int score = 0;

    double elapsed_time = 0;
    double next_invader_spawn_time = 0;

    int num_games_played = 0;

    Rml::Array<Invader, numInvaders> invaders;

    // Start a new game.
    void StartGame(Rml::DataModelHandle model, Rml::Event & /*ev*/, const Rml::VariantList & /*arguments*/) {
        health = 100;
        charge = 30;
        score = 0;
        elapsed_time = 0;
        next_invader_spawn_time = 0;
        num_games_played += 1;

        for (Invader &invader: invaders)
            invader.health = 0;

        model.DirtyVariable("health");
        model.DirtyVariable("charge");
        model.DirtyVariable("score");
        model.DirtyVariable("elapsed_time");
        model.DirtyVariable("num_games_played");
        model.DirtyVariable("invaders");
    }

    // Fire on the invader of the given index (first argument).
    void Fire(Rml::DataModelHandle model, Rml::Event & /*ev*/, const Rml::VariantList &arguments) {
        if (arguments.size() != 1)
            return;
        const auto index = arguments[0].Get<std::size_t>();
        if (index >= invaders.size())
            return;

        Invader &invader = invaders[index];
        if (health <= 0 || invader.health <= 0)
            return;

        const float new_health = Rml::Math::Max(invader.health - charge * Rml::Math::SquareRoot(charge), 0.0f);

        charge = 30.f;
        score += int(invader.health - new_health) + 1000 * (new_health == 0);

        invader.health = new_health;

        model.DirtyVariable("invaders");
        model.DirtyVariable("charge");
        model.DirtyVariable("score");
    }

} data;

bool InvadersExample::Initialize(Rml::Context* context) {
    Rml::DataModelConstructor constructor = context->CreateDataModel("invaders");
    if (!constructor)
        return false;

    // Register a custom getter for the Colourb type.
    constructor.RegisterScalar<Rml::Colourb>(
            [](const Rml::Colourb &color, Rml::Variant &variant) { variant = "rgba(" + Rml::ToString(color) + ')'; });
    // Register a transform function for formatting time
    constructor.RegisterTransformFunc("format_time", [](const Rml::VariantList &arguments) -> Rml::Variant {
        if (arguments.empty())
            return {};
        const double t = arguments[0].Get<double>();
        const int minutes = int(t) / 60;
        const double seconds = t - 60.0 * double(minutes);
        return Rml::Variant(Rml::CreateString(10, "%02d:%05.2f", minutes, seconds));
    });

    // Structs are registered by adding all their members through the returned handle.
    if (auto invader_handle = constructor.RegisterStruct<Invader>()) {
        invader_handle.RegisterMember("name", &Invader::name);
        invader_handle.RegisterMember("sprite", &Invader::sprite);
        invader_handle.RegisterMember("color", &Invader::color);
        invader_handle.RegisterMember("max_health", &Invader::max_health);
        invader_handle.RegisterMember("charge_rate", &Invader::charge_rate);
        invader_handle.RegisterMember("health", &Invader::health);
        invader_handle.RegisterMember("charge", &Invader::charge);
    }

    // We can even have an Array of Structs, infinitely nested if we so desire.
    // Make sure the underlying type (here Invader) is registered before the array.
    constructor.RegisterArray<decltype(data.invaders)>();

    // Now we can bind the variables to the model.
    constructor.Bind("invaders", &data.invaders);
    constructor.Bind("health", &data.health);
    constructor.Bind("charge", &data.charge);
    constructor.Bind("score", &data.score);
    constructor.Bind("elapsed_time", &data.elapsed_time);
    constructor.Bind("num_games_played", &data.num_games_played);

    // This function will be called when the user clicks on the (re)start game button.
    constructor.BindEventCallback("start_game", &InvadersData::StartGame, &data);
    // This function will be called when the user clicks on any of the invaders.
    constructor.BindEventCallback("fire", &InvadersData::Fire, &data);

    modelHandle = constructor.GetModelHandle();

    return true;
}

void InvadersExample::Update(const double dt) {
    using namespace Rml;

    if (data.health == 0)
        return;

    data.elapsed_time += dt;
    modelHandle.DirtyVariable("elapsed_time");

    // Steadily increase the player charge.
    data.charge = Math::Min(data.charge + float(40.0 * dt), 100.f);
    modelHandle.DirtyVariable("charge");

    // Add new invaders at the scheduled time.
    if (data.elapsed_time >= data.next_invader_spawn_time) {
        constexpr int num_items = 4;
        static Array<String, num_items> names = { "Angry invader", "Harmless invader", "Deceitful invader", "Cute invader" };
        static Array<String, num_items> sprites = { "icon-invader", "icon-flag", "icon-game", "icon-waves" };
        static Array<Colourb, num_items> colors = {{{ 255, 40, 30 }, { 20, 40, 255 }, { 255, 255, 30 }, { 230, 230, 230 }}};

        Invader new_invader;
        new_invader.name = names[Math::RandomInteger(num_items)];
        new_invader.sprite = sprites[Math::RandomInteger(num_items)];
        new_invader.color = colors[Math::RandomInteger(num_items)];

        new_invader.max_health = 300.f + float(30.0 * data.elapsed_time) + Math::RandomReal(300.f);
        new_invader.charge_rate = 10.f + Math::RandomReal(50.f);

        new_invader.health = new_invader.max_health;

        // Find an available slot to spawn the new invader in.
        const int i_begin = Math::RandomInteger(numInvaders);
        for (int i = 0 ; i < numInvaders ; i++) {
            Invader &invader = data.invaders[(i + i_begin) % numInvaders];
            if (invader.health <= 0) {
                invader = std::move(new_invader);
                modelHandle.DirtyVariable("invaders");
                break;
            }
        }

        // Add new invaders at steadily decreasing time intervals.
        data.next_invader_spawn_time = data.elapsed_time + 60.0 / (incomingInvadersRate + 0.1 * data.elapsed_time);
    }

    // Iterate through the invaders and fire at the player.
    for (Invader &invader: data.invaders) {
        if (invader.health > 0) {
            invader.charge = invader.charge + invader.charge_rate * float(dt);

            if (invader.charge >= 100) {
                data.health = Math::Max(data.health - float(10.0 * dt), 0.0f);
                modelHandle.DirtyVariable("health");
            }

            if (invader.charge >= 120)
                invader.charge = 0;

            modelHandle.DirtyVariable("invaders");
        }
    }
}
