# Actividad 2 – Prolog

## Generación automática de horarios

Este trabajo implementa un sistema en Prolog que genera un cronograma semanal de empleados, respetando:

- Días de franco
- Compatibilidad entre oficio y sector
- Cobertura de turnos
- Presencia de vendedor

## Cómo ejecutar

Abrir SWI-Prolog y ejecutar:

```prolog
['actividad2.pl'].
ver_plan.

```

## Autor

Cristian Collins  
Licenciatura en Gestión de Recursos Tecnológicos

## consultas
## consultas

CONSULTA | QUE DEMUESTRA
---------|--------------
ver_plan. | Genera y muestra el cronograma completo semanal
generar_plan(Plan). | Genera el plan como estructura de datos
ver_horario_empleado(e1). | Muestra el horario completo de un empleado
generar_plan(Plan), horario_empleado(Plan, e1, H). | Obtiene el horario del empleado dentro de un plan
generar_plan(Plan), dias_trabaja(Plan, e1, Dias). | Lista los días que trabaja el empleado
generar_plan(Plan), cantidad_dias_trabajados(Plan,e1,C) | Cuenta los días trabajados (deben ser 6)
dia_franco(e1, Dia). | Devuelve el día libre del empleado
generar_plan(Plan), quienes_trabajan(Plan,lunes,manana,L) | Lista quién trabaja en un día y turno
empleados_disponibles_dia(lunes, Empleados). | Lista empleados disponibles ese día
puede_cubrir(e1, comidas_elaboradas, manana, martes). | Verifica si un empleado puede cubrir un puesto
generar_plan(Plan), plan_ok(Plan). | Valida TODO el sistema (validación global)
generar_plan(Plan), sin_superposicion(Plan). | Verifica que no haya doble turno por día
generar_plan(Plan), cobertura_toda_la_semana(Plan). | Verifica cobertura completa todos los días
generar_plan(Plan), cobertura_vendedor_plan(Plan). | Verifica que siempre haya vendedor
generar_plan(Plan), todos_cumplen_seis_dias(Plan). | Verifica que todos trabajen 6 días
generar_plan(Plan), mostrar_plan(Plan). | Genera y muestra el plan manualmente
generar_plan(Plan), horario_empleado(Plan,e1,H1), horario_empleado(Plan,e2,H2). | Analiza múltiples empleados en un mismo plan
generar_plan(Plan), dias_trabaja(Plan,e3,Dias), horario_empleado(Plan,e3,H). | Combina días trabajados + detalle del horario
empleado(E). | Lista todos los empleados
sector(S). | Lista todos los sectores
turno(T). | Lista todos los turnos
dia(D). | Lista todos los días
sabe(e1, X). | Muestra habilidades de un empleado
sector_requiere(venta, X). | Muestra qué requiere un sector
sector_habilitado(venta, Turno). | Muestra turnos habilitados de un sector
generar_asignaciones_dia(lunes, A). | Genera asignaciones de un día (debug)
disponible(e1, lunes). | Verifica disponibilidad de un empleado
