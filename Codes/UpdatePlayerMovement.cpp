void UpdatePlayerMovement( float& x, float& y, float& angle, float& speed) {
    if (Play::KeyDown(VK_RIGHT)){
        angle = angle + 0.1;
    }
    if (Play::KeyDown(VK_LEFT)){
        angle = angle - 0.1;
    }

    x = x + sin( angle ) * speed;
    y = y - cos( angle ) * speed;

    if (Play::KeyDown(VK_UP)){
        speed = speed + 0.2;
    }
    if (Play::KeyDown(VK_DOWN)){
        speed = speed - 0.2;
    }

}