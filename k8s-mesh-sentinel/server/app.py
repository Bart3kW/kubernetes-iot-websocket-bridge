import asyncio
import websockets
import json

# Active clients
CLIENTS = {}

async def broadcast(message_dict):
    """Broadcasting to all users"""
    if CLIENTS:
        message = json.dumps(message_dict)
        # asynchro tasks
        tasks = [asyncio.create_task(ws.send(message)) for ws in CLIENTS]
        await asyncio.wait(tasks)

async def handler(websocket):
    ip = websocket.remote_address[0]
    
    try:
        # handshake
        first_msg = await websocket.recv()
        data = json.loads(first_msg)
        name = data.get("name", "Nieznajomy")
        
        # save session
        CLIENTS[websocket] = {"name": name, "ip": ip}
        print(f"Nowe połączenie: {name} ({ip})")
        
        # notification
        await broadcast({"type": "system", "msg": f"[{name}] dolaczyl z IP {ip}"})
        
        async for message in websocket:
            data = json.loads(message)
            text = data.get("msg", "")
            print(f"Otrzymano od {name}: {text}")
           
            # broadcasting message
            await broadcast({"type": "chat", "name": name, "msg": text})
            
    except websockets.exceptions.ConnectionClosed:
        pass
    finally:
        # disconecting
        if websocket in CLIENTS:
            user_info = CLIENTS.pop(websocket)
            print(f"Rozłączono: {user_info['name']}")
            await broadcast({"type": "system", "msg": f"[{user_info['name']}] opuscil czat."})

async def main():
    print("Serwer WebSocket uruchomiony na porcie 8765...")
    async with websockets.serve(handler, "0.0.0.0", 8765):
        await asyncio.Future() 

if __name__ == "__main__":
    asyncio.run(main())
