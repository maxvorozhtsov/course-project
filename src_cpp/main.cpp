#include "courier.hpp"
#include "order.hpp"

#include <clocale>
#include <iostream>

namespace
{

    void InspectCourierByReference(const courier::Courier& courierRef)
    {
        std::cout << "[Проверка по ссылке] ";
        courierRef.PrintStatus();
    }

} // namespace

int main()
{
    std::setlocale(LC_ALL, "Russian");

    std::cout << "=========================================================\n";
    std::cout << "1. ДЕМОНСТРАЦИЯ ВРЕМЕНИ ЖИЗНИ (КОМПОЗИЦИЯ И АГРЕГАЦИЯ)\n";
    std::cout << "=========================================================\n";

    courier::Courier motoCourier{ "Алексей", courier::Courier::VehicleType::eMotorcycle, 15.0 };
    motoCourier.OpenShift();

    courier::Courier autoCourier{ "Дмитрий", courier::Courier::VehicleType::eCar, 100.0 };
    autoCourier.OpenShift();

    {
        std::cout << "\n--- Вход во вложенный блок (создание Заказа) ---\n";
        courier::Order heavyOrder{ 101, "ул. Ленина, 45, кв. 12", "Холодильник малый", 28.0, 25000.0, true };
        heavyOrder.PrintOrderDetails();

        std::cout << "\n--- Попытка нарушить правило перегруза ---\n";
        heavyOrder.AssignCourier(&motoCourier);

        std::cout << "\n--- Корректное назначение подходящему курьеру (Агрегация) ---\n";
        heavyOrder.AssignCourier(&autoCourier);

        std::cout << "\n--- Перевод в статус 'В пути' и попытка нарушить Правило №15 ---\n";
        heavyOrder.StartDelivery();
        heavyOrder.TryRaiseCargoValue(30000.0);

        std::cout << "\n--- Попытка закрыть заказ без подтверждения получателя (Правило №6) ---\n";
        heavyOrder.CompleteDelivery(false);

        std::cout << "\n--- Корректное вручение груза ---\n";
        heavyOrder.CompleteDelivery(true);
        heavyOrder.PrintOrderDetails();

        std::cout << "\n--- Выход из вложенного блока (уничтожение Заказа) ---\n";
    }

    std::cout << "\n--- Проверка после уничтожения заказа (Агрегация) ---\n";
    std::cout << "Заказ уничтожен, но курьеры продолжают жить:\n";
    InspectCourierByReference(autoCourier);

    std::cout << "\n=========================================================\n";
    std::cout << "2. ДЕМОНСТРАЦИЯ РАБОТЫ С ПАМЯТЬЮ И УКАЗАТЕЛЯМИ\n";
    std::cout << "=========================================================\n";

    std::cout << "\n--- Динамический объект через new/delete ---\n";
    auto* dynamicCourier = new courier::Courier{ "Сергей", courier::Courier::VehicleType::eBicycle, 12.0 };
    dynamicCourier->OpenShift();
    dynamicCourier->PrintStatus();
    delete dynamicCourier;

    std::cout << "\n--- Динамический массив объектов (Order) ---\n";
    constexpr int ORDER_ARRAY_SIZE = 2;
    auto* orderArray = new courier::Order[ORDER_ARRAY_SIZE];
    orderArray[0].PrintOrderDetails();
    delete[] orderArray;

    std::cout << "\n--- Массив указателей на динамические объекты (Courier*) ---\n";
    constexpr int STAFF_COUNT = 2;
    auto** courierFleet = new courier::Courier * [STAFF_COUNT];
    courierFleet[0] = new courier::Courier{ "Иван", courier::Courier::VehicleType::eCar, 150.0 };
    courierFleet[1] = new courier::Courier{ "Елена", courier::Courier::VehicleType::eFoot, 8.0 };

    for (int i = 0; i < STAFF_COUNT; ++i)
    {
        courierFleet[i]->OpenShift();
        courierFleet[i]->PrintStatus();
    }

    for (int i = 0; i < STAFF_COUNT; ++i)
    {
        delete courierFleet[i];
    }
    delete[] courierFleet;

    std::cout << "\n--- Завершение main (уничтожение статических курьеров) ---\n";
    return 0;
}
