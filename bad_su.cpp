#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>

const int LINES_PER_FRAME = 30;  // 与 jp2a 的 --height 参数一致
const int FPS = 24;              // 帧率（需与 ffmpeg 提取的 fps 一致）

// 清屏并移动光标到左上角（Linux 终端有效）
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void bad_apple() {
    std::ifstream file("ascii_frames.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open ascii_frames.txt!" << std::endl;
        return;
    }

    std::vector<std::string> frameBuffer;
    std::string line;
    auto frameDelay = std::chrono::milliseconds(1000 / FPS);

    while (std::getline(file, line)) {
        frameBuffer.push_back(line);
        if (frameBuffer.size() == LINES_PER_FRAME) {
            clearScreen();
            // 一次性输出整个帧，减少闪烁
            for (const auto& ln : frameBuffer) {
                std::cout << ln << "\n";
            }
            std::cout.flush();  // 强制刷新输出缓冲区
            frameBuffer.clear();
            // 控制帧率
            std::this_thread::sleep_until(
                std::chrono::steady_clock::now() + frameDelay
            );
        }
    }

    file.close();
}

int getTerminalWidth() {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return ws.ws_col;
}

void printCenter(const std::string& text) {
    // 要打印的文本
    //std::string text = "Hello, World!";
    int textLength = text.length();

    // 计算文本居中的位置
    int padding = (getTerminalWidth() - textLength) / 2;

    // 设置整行背景为红色，字体为黑色
    std::cout << "\033[41;30m"; // 41: 背景红色, 30: 字体黑色

    // 填充左侧空白
    for (int i = 0; i < padding; ++i) {
        std::cout << " ";
    }

    // 打印文本
    std::cout << text;

    // 填充右侧空白
    for (int i = 0; i < getTerminalWidth() - padding - textLength; ++i) {
        std::cout << " ";
    }

    // 重置颜色
    std::cout << "\033[0m" << std::endl;
}

int main() {
    printCenter("WARN!");
	std::cout << "Executing this procedure may cause devastating harm to your device, please confirm that it is executed" << std::endl;
    std::cout << "执行该程序可能对你的设备造成破坏性伤害，请确认执行 (y/N)";
	std::string input;
	std::cin >> input;
	if (input == "N" || input == "n" || input == "") {
		return 1;
	}
	printCenter("WARN!");
	std::cout << "Please confirm that you want to proceed with the procedure and that the author will not be held responsible for any damages" << std::endl;
	std::cout << "请确认你要继续执行该程序，如果出现任何损失，作者不负任何责任 (y/N)";
	std::cin >> input;
	if (input == "N" || input == "n" || input == "") {
		return 1;
	}
	printCenter("WARN!");
	std::cout << "Please don't bring up any mistakes, it will cause some people unnecessary harm, do you agree?" << std::endl;
	std::cout << "出现任何错误请不要提出来，这会使一些人受到不必要的伤害，是否同意? (y/N)";
	std::cin >> input;
	if (input == "N" || input == "n" || input == "") {
		return 1;
	}
    std::cout << "INFO: System initialization started." << std::endl;
    std::cout << "INFO: Loading kernel modules..." << std::endl;
    std::cout << "INFO: Kernel modules loaded successfully." << std::endl;

    // Simulating hardware checks
    std::cout << "INFO: Checking hardware components..." << std::endl;
    std::cout << "INFO: CPU detected: Intel(R) Core(TM) i7-10700K." << std::endl;
    std::cout << "INFO: RAM detected: 16GB DDR4." << std::endl;
    std::cerr << "WARNING: GPU not detected. Using integrated graphics." << std::endl;
    std::cout << "INFO: Storage devices detected: 1TB SSD, 2TB HDD." << std::endl;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Simulating file system checks
    std::cout << "INFO: Verifying file system integrity..." << std::endl;
    std::cerr << "ERROR: File system corruption detected on /dev/sda1." << std::endl;
    std::cout << "INFO: Attempting to repair file system..." << std::endl;
    std::cout << "INFO: File system repair completed successfully." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    // Simulating network configuration
    std::cout << "INFO: Configuring network settings..." << std::endl;
    std::cerr << "ERROR: Unable to connect to DHCP server." << std::endl;
    std::cout << "INFO: Using static IP configuration." << std::endl;
    std::cout << "INFO: Network configuration completed." << std::endl;

    // Simulating service startup
    std::cout << "INFO: Starting system services..." << std::endl;
    std::cout << "INFO: Service 'ssh' started successfully." << std::endl;
    std::cerr << "ERROR: Service 'apache2' failed to start. Port 80 already in use." << std::endl;
    std::cout << "INFO: Service 'mysql' started successfully." << std::endl;
    std::cerr << "WARNING: Service 'cron' is running with limited functionality." << std::endl;

    // Simulating user login
    std::cout << "INFO: Starting login manager..." << std::endl;
    std::cout << "INFO: User 'admin' logged in successfully." << std::endl;
    std::cerr << "WARNING: Failed login attempt for user 'guest'." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Simulating application startup
    std::cout << "INFO: Launching desktop environment..." << std::endl;
    std::cout << "INFO: Desktop environment loaded successfully." << std::endl;
    std::cerr << "ERROR: Application 'firefox' crashed on startup." << std::endl;
    std::cout << "INFO: Application 'libreoffice' started successfully." << std::endl;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Simulating background tasks
    std::cout << "INFO: Running background tasks..." << std::endl;
    std::cout << "INFO: Task 'backup' completed successfully." << std::endl;
    std::cerr << "ERROR: Task 'update' failed. No internet connection." << std::endl;
    std::cout << "INFO: Task 'cleanup' completed successfully." << std::endl;

    // Simulating system monitoring
    std::cout << "INFO: Monitoring system performance..." << std::endl;
    std::cerr << "WARNING: High CPU usage detected (95%)." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "INFO: Memory usage is within normal limits." << std::endl;
    std::cerr << "WARNING: Disk usage on /dev/sda1 is at 90%." << std::endl;

    // Simulating system shutdown
    std::cout << "INFO: Initiating system shutdown..." << std::endl;
    std::cout << "INFO: Saving system state..." << std::endl;
    std::cerr << "ERROR: Unable to save state for application 'firefox'." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "INFO: System state saved successfully." << std::endl;
    std::cout << "INFO: Stopping system services..." << std::endl;
    std::cout << "INFO: Service 'ssh' stopped successfully." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "INFO: Service 'mysql' stopped successfully." << std::endl;
    std::cerr << "WARNING: Service 'cron' did not stop gracefully." << std::endl;
    std::cout << "INFO: All services stopped." << std::endl;
    std::cout << "INFO: Powering off..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    for (int i = 0; i < 100000; ++i) {
		std::cout << "Bad ";
		// std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	std::cout << std::endl;
	clearScreen();
	std::cout << "Bad Apple!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    bad_apple();
    return 0;
}
