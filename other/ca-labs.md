# CA Labs

## Lab1: Pipleline

- Pipeline Hazards
    - Structural Hazards
        - Hardware doesn't support the combination of instructions.
        - When using single memory for both instructions and data.
    - Data Hazards
        - Dependence between instructions
        - Situations:

            ```text
            EX/MEM.Rd = ID/EX.Rs -> Forward from EX/MEM to EX
            MEM/WB.Rd = ID/EX.Rs -> Forward from MEM/WB to EX
            ```

            Also require `Rd != 0` and `RegWrite` is true.

            Forward from **EX/MEM has higher priority than MEM/WB**, because it has the more recent value.

            And there is the case where load is immediately followed by store:

            ```text
            MEM/WB.Rd = ID/EX.Rs -> Forward from MEM/WB to MEM
            ```

        - Forwarding (also called bypassing)
            - Add extra hardware to retrieve the missing item early from the internal resources.
            - Can't handle load-use hazards. Need to stall the pipeline.
    - Control Hazards
        - Make desicions based on the results of previous instructions.
        - Stall.
        - Prediction
            - Always taken/always not taken.
            - Dynamic hardware predictor.
