% =========================
% ACTIVIDAD PROLOG
% GENERACION AUTOMATICA DE HORARIOS
% VERSION FINAL MEJORADA
% =========================

% =========================
% DATOS BASE
% =========================

% Dias de la semana
dia(lunes).
dia(martes).
dia(miercoles).
dia(jueves).
dia(viernes).
dia(sabado).
dia(domingo).

% Turnos disponibles
turno(manana).
turno(tarde).
turno(noche).

% Sectores de trabajo
sector(comidas_elaboradas).
sector(panaderia).
sector(pastas).
sector(venta).

% Oficio requerido por cada sector
sector_requiere(comidas_elaboradas, cocinero).
sector_requiere(panaderia,          panadero).
sector_requiere(pastas,             fabrica_pasta).
sector_requiere(venta,              vendedor).

% Turnos habilitados por sector
sector_habilitado(comidas_elaboradas, manana).
sector_habilitado(comidas_elaboradas, tarde).
sector_habilitado(comidas_elaboradas, noche).

sector_habilitado(panaderia, manana).
sector_habilitado(panaderia, tarde).
sector_habilitado(panaderia, noche).

sector_habilitado(pastas, manana).
sector_habilitado(pastas, tarde).
sector_habilitado(pastas, noche).

sector_habilitado(venta, manana).
sector_habilitado(venta, tarde).
% venta no opera de noche

% Empleados
empleado(e1).
empleado(e2).
empleado(e3).
empleado(e4).
empleado(e5).

% Habilidades de cada empleado
sabe(e1, cocinero).
sabe(e1, vendedor).

sabe(e2, panadero).
sabe(e2, vendedor).

sabe(e3, fabrica_pasta).
sabe(e3, vendedor).

sabe(e4, cocinero).
sabe(e4, panadero).

sabe(e5, fabrica_pasta).
sabe(e5, vendedor).

% Dia de franco semanal por empleado
franco(e1, lunes).
franco(e2, martes).
franco(e3, miercoles).
franco(e4, jueves).
franco(e5, domingo).

% Lista ordenada de dias de la semana
dias_semana([lunes, martes, miercoles, jueves, viernes, sabado, domingo]).

% =========================
% REGLAS BASE
% =========================

% Un empleado esta disponible un dia si ese dia no es su franco
disponible(Empleado, Dia) :-
    empleado(Empleado),
    dia(Dia),
    \+ franco(Empleado, Dia).

% Un empleado puede cubrir un sector en un turno si:
%   - esta disponible ese dia
%   - conoce el oficio requerido por el sector
%   - el sector esta habilitado para ese turno
puede_cubrir(Empleado, Sector, Turno, Dia) :-
    disponible(Empleado, Dia),
    sector_requiere(Sector, Oficio),
    sabe(Empleado, Oficio),
    sector_habilitado(Sector, Turno).

% Lista de empleados disponibles en un dia determinado
empleados_disponibles_dia(Dia, Empleados) :-
    findall(E, disponible(E, Dia), Empleados).

% =========================
% GENERACION AUTOMATICA
% =========================

% Genera todas las asignaciones de un dia:
% cada empleado disponible recibe exactamente un turno y un sector
generar_asignaciones_dia(Dia, AsignacionesDia) :-
    empleados_disponibles_dia(Dia, Empleados),
    asignar_empleados_dia(Empleados, Dia, AsignacionesDia),
    cobertura_minima_dia(AsignacionesDia),
    cobertura_vendedor_dia(AsignacionesDia).

% Caso base: sin empleados, sin asignaciones
asignar_empleados_dia([], _, []).

% Asigna un turno y sector valido a cada empleado del dia
asignar_empleados_dia(
    [Empleado|Resto],
    Dia,
    [asignado(Dia, Turno, Empleado, Sector)|AsignacionesResto]
) :-
    puede_cubrir(Empleado, Sector, Turno, Dia),
    asignar_empleados_dia(Resto, Dia, AsignacionesResto).

% Debe haber al menos un empleado en cada turno del dia
cobertura_minima_dia(AsignacionesDia) :-
    member(asignado(_, manana, _, _), AsignacionesDia),
    member(asignado(_, tarde,  _, _), AsignacionesDia),
    member(asignado(_, noche,  _, _), AsignacionesDia).

% Debe haber al menos un vendedor asignado a venta en manana o tarde
% (los parentesis explicitan el alcance del operador de disyuncion)
cobertura_vendedor_dia(AsignacionesDia) :-
    (   member(asignado(_, manana, _, venta), AsignacionesDia)
    ;   member(asignado(_, tarde,  _, venta), AsignacionesDia)
    ).

% Genera el plan completo de la semana y lo valida
generar_plan(Plan) :-
    dias_semana(Dias),
    generar_plan_dias(Dias, Plan),
    plan_ok(Plan).

% Caso base
generar_plan_dias([], []).

% Genera asignaciones dia por dia y acumula el plan
generar_plan_dias([Dia|RestoDias], PlanCompleto) :-
    generar_asignaciones_dia(Dia, AsignacionesDia),
    generar_plan_dias(RestoDias, PlanResto),
    append(AsignacionesDia, PlanResto, PlanCompleto).

% =========================
% VALIDACIONES DEL PLAN
% =========================

% Verifica que una asignacion individual sea valida
asignacion_valida_plan(asignado(Dia, Turno, Empleado, Sector)) :-
    puede_cubrir(Empleado, Sector, Turno, Dia).

% Verifica que todas las asignaciones del plan sean validas
cronograma_valido(Plan) :-
    forall(
        member(Asignacion, Plan),
        asignacion_valida_plan(Asignacion)
    ).

% Un empleado no puede tener dos turnos distintos el mismo dia
% Tampoco puede aparecer dos veces en el mismo dia y turno
sin_superposicion(Plan) :-
    \+ (
        member(asignado(Dia, Turno1, Empleado, _), Plan),
        member(asignado(Dia, Turno2, Empleado, _), Plan),
        Turno1 \= Turno2
    ),
    \+ (
        member(asignado(Dia, Turno, Empleado, Sector1), Plan),
        member(asignado(Dia, Turno, Empleado, Sector2), Plan),
        Sector1 \= Sector2
    ).

% Obtiene los dias trabajados por un empleado (sin repetidos)
trabaja_dia_plan(Plan, Empleado, Dia) :-
    member(asignado(Dia, _, Empleado, _), Plan).

cantidad_dias_trabajados(Plan, Empleado, Cantidad) :-
    findall(Dia, trabaja_dia_plan(Plan, Empleado, Dia), DiasRepetidos),
    sort(DiasRepetidos, DiasUnicos),
    length(DiasUnicos, Cantidad).

% Cada empleado debe trabajar exactamente 6 dias (1 franco semanal)
todos_cumplen_seis_dias(Plan) :-
    forall(
        empleado(E),
        cantidad_dias_trabajados(Plan, E, 6)
    ).

% Verifica cobertura de un turno especifico en un dia del plan
cobertura_turno_plan(Plan, Dia, Turno) :-
    member(asignado(Dia, Turno, _, _), Plan).

% Verifica que un dia tenga cobertura en los tres turnos
cobertura_dia_plan(Plan, Dia) :-
    cobertura_turno_plan(Plan, Dia, manana),
    cobertura_turno_plan(Plan, Dia, tarde),
    cobertura_turno_plan(Plan, Dia, noche).

% Verifica cobertura completa en todos los dias de la semana
cobertura_toda_la_semana(Plan) :-
    forall(
        dia(Dia),
        cobertura_dia_plan(Plan, Dia)
    ).

% Verifica que haya vendedor en venta cada dia (manana o tarde)
cobertura_vendedor_plan(Plan) :-
    forall(
        dia(Dia),
        (   member(asignado(Dia, manana, _, venta), Plan)
        ;   member(asignado(Dia, tarde,  _, venta), Plan)
        )
    ).

% Validacion general del plan completo
plan_ok(Plan) :-
    cronograma_valido(Plan),
    sin_superposicion(Plan),
    todos_cumplen_seis_dias(Plan),
    cobertura_toda_la_semana(Plan),
    cobertura_vendedor_plan(Plan).

% =========================
% CONSULTAS UTILES
% =========================

% Horario completo de un empleado dentro de un plan
horario_empleado(Plan, Empleado, Horario) :-
    findall(
        Dia-Turno-Sector,
        member(asignado(Dia, Turno, Empleado, Sector), Plan),
        Horario
    ).

% Lista de dias en que trabaja un empleado
dias_trabaja(Plan, Empleado, Dias) :-
    findall(Dia,
        member(asignado(Dia, _, Empleado, _), Plan),
        DiasRepetidos),
    sort(DiasRepetidos, Dias).

% Dia franco de un empleado
dia_franco(Empleado, Dia) :-
    franco(Empleado, Dia).

% Lista de empleados y sectores que trabajan en un dia y turno dados
quienes_trabajan(Plan, Dia, Turno, Lista) :-
    findall(
        Empleado-Sector,
        member(asignado(Dia, Turno, Empleado, Sector), Plan),
        Lista
    ).

% =========================
% VISUALIZACION
% =========================

% Muestra todas las asignaciones del plan en pantalla
mostrar_plan([]).
mostrar_plan([asignado(Dia, Turno, Empleado, Sector)|Resto]) :-
    write(Dia),      write(' | '),
    write(Turno),    write(' | '),
    write(Empleado), write(' | '),
    write(Sector),   nl,
    mostrar_plan(Resto).

% Genera y muestra un plan valido directamente
ver_plan :-
    generar_plan(Plan),
    mostrar_plan(Plan).

% Genera un plan y muestra el horario de un empleado especifico
ver_horario_empleado(Empleado) :-
    generar_plan(Plan),
    horario_empleado(Plan, Empleado, Horario),
    write(Horario), nl.

