# ipac
This is ipv4 address calculator

## output ( decimal and binary notation )
- Host address
- Subnet mask
- Network address
- Broadcast address

## usage
```
git clone https://github.com/homoluctus/ipac.git

# compile
make

# example
./ipac 192.168.0.1 24

---------------------------------------------------
| Host        |      192.     168.       0.       1 |
|             | 11000000.10101000.00000000.00000001 |
---------------------------------------------------
| Subnet Mask |      255.     255.     255.       0 |
|             | 11111111.11111111.11111111.00000000 |
---------------------------------------------------
| Network     |      192.     168.       0.       0 |
|             | 11000000.10101000.00000000.00000000 |
---------------------------------------------------
| Broadcast   |      192.     168.       0.     255 |
|             | 11000000.10101000.00000000.11111111 |
---------------------------------------------------
```
