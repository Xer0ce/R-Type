/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** IHandleCommand
*/

#pragma once

class IHandleCommand {
    public:
        IHandleCommand();
        ~IHandleCommand();

        virtual void initCommand() = 0;
        virtual void handleCommand() = 0;
    private:
};

