#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "equipment/weapon/weaponsList.h"
#include "types.h"

class Player : public Entity
{
private:
    u8 m_hp;
    u8 m_armor;
    float m_speed, m_jumpForce, m_gravity;
    bool m_isGrounded, m_isAlive;
    sf::RectangleShape m_colider;
    sf::Texture m_texture;
    sf::Vector2f m_velocity;
        
private:
    Pistols pistol
    {
        "textures/weapon/pistol/Pistol - Second version sprite sheets (80x48)/pistol-all.png",
        "textures/weapon/shot/bullet.png",
        "textures/particles/smoke.png",
        {"sounds/shot/pistol/shot1.wav", "sounds/shot/assault/shot1[AK-74U].wav"}
    };
    AssaultRiffle assaultRiffle
    {
        "textures/weapon/assault/shootV2.png",
        "textures/weapon/shot/bullet.png",
        "textures/particles/smoke.png",
        {"sounds/shot/assault/shot1[AK-74U].wav"}
    };
    ShotGuns shotgun
    {
        "textures/weapon/shotgun/shoot.png",
        "textures/weapon/shot/bullet.png",
        "textures/particles/smoke.png",
        {"sounds/shot/pistol/shot1.wav"}
    };
    
    Pistols currentPistol{ "", "", "", {} };
    AssaultRiffle currentAssault{ "", "", "", {} };
    ShotGuns currentShotgun{ "", "", "", {} };

private:
    u8 selectedWeapon;
    sf::Vector2f m_weaponPosition;
    std::vector<Weapon*> m_weaponsInInventory;
    
    //MachineGuns currentMachine;
    //Energyguns currentEnergy;
    //ExplosiveGuns currentExplosive;


    enum WeaponType
    {
        PRIMARILY = 1,
        SECONDARY,
        TERTIARY,
        QUATERNARY
    };

private:
    __forceinline const void hideAllWeapons() const
    {
        for (auto& weapon : this->m_weaponsInInventory)
            weapon->Hide();
    }

private:
    void handleJumpInput(float targetHeight);
    void applyGravity(float deltaTime);

public:
    Player(sf::Vector2f _size, sf::Color _color, sf::Vector2f _position, u8 _hp, u8 _armor);
    virtual ~Player() override;
    
public:
    void updateInput(const sf::RenderWindow* target, float deltaTime);
    void updateWindowBoundsCollision(const sf::RenderWindow* target);
    void updateWeapon(const sf::RenderWindow* target, float deltaTime);
    void update(const sf::RenderWindow* target, float deltaTime);
    void render(sf::RenderWindow* window);
    void renderWeapon(sf::RenderWindow* target);
        
public:
    // Setters
    __forceinline virtual void setColor(sf::Color color) override { this->m_colider.setFillColor(color); }
    __forceinline virtual void setSize(sf::Vector2f size) override { this->m_colider.setSize(size); }
    __forceinline virtual void setPosition(sf::Vector2f position) override { this->m_colider.setPosition(position); }
    __forceinline void setHp(u8 hp) { this->m_hp = hp; }
    __forceinline void setArmorHp(u8 armor) { this->m_armor = armor; }
	
    // Getters	
    __forceinline const virtual sf::Color getColor() const override { return this->m_colider.getFillColor(); }
    __forceinline const virtual sf::Vector2f getSize() const override { return this->m_colider.getSize(); }
    __forceinline const virtual sf::Vector2f getPosition() const override {return this->m_colider.getPosition(); }
    __forceinline const virtual sf::Vector2f getVelocity() const override {return this->m_velocity; }
    __forceinline const u8 getHp() const { return this->m_hp; }
    __forceinline const u8 getArmor() const { return this->m_armor; }
    const bool getDirection() const;

public:
    // Other
    const void jump();
    const void kill() override;
    __forceinline const bool isAlive() const { return this->m_hp <= 0 ? false : true; }
};

#endif