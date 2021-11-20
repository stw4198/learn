def sig_choice(sig):
    if sig == "heysham_2":
        components = ["heysham_2",\
        "torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
        other = ["heysham_2",\
        "torness_full",\
        "world",\
        "geo",\
        "fn",\
        ]
        signal_components = ["heysham_2"]
        background_components = ["torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
    elif sig == "heysham_full":
        components = ["heysham_full",\
        "torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
        other = ["heysham_full",\
        "heysham_2",\
        "torness_full",\
        "world",\
        "geo",\
        "fn",\
        ]
        signal_components = ["heysham_full"]
        background_components = ["torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
    elif sig == "torness_full":
        components = ["heysham_2",\
        "torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
        other = ["heysham_2",\
        "torness_full",\
        "world",\
        "geo",\
        "fn",\
        ]
        signal_components = ["torness_full"]
        background_components = ["heysham_2",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
    elif sig == "torness_only":
        components = ["torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
        other = ["heysham_2",\
        "torness_full",\
        "world",\
        "geo",\
        "fn",\
        ]
        signal_components = ["torness_full"]
        background_components = ["world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
    elif sig == "heytor":
        components = ["heysham_2",\
        "torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
        other = ["heysham_2",\
        "torness_full",\
        "world",\
        "geo",\
        "fn",\
        ]
        signal_components = ["heysham_2","torness_full"]
        background_components = ["world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
    elif sig == "hartlepool":
        components = ["hartlepool_1",\
        "hartlepool_2",\
        "heysham_full",\
        "torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
        other = ["hartlepool_1",\
        "hartlepool_2",\
        "heysham_full",\
        "torness_full",\
        "world",\
        "geo",\
        "fn",\
        ]
        signal_components = ["hartlepool_1","hartlepool_2"]
        background_components = ["heysham_full",\
        "torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
    elif sig == "hartlepool_1":
        components = ["hartlepool_1",\
        "hartlepool_2",\
        "heysham_full",\
        "torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]
        other = ["hartlepool_1",\
        "hartlepool_2",\
        "heysham_full",\
        "torness_full",\
        "world",\
        "geo",\
        "fn",\
        ]
        signal_components = ["hartlepool_1"]
        background_components = ["hartlepool_2",\
        "heysham_full",\
        "torness_full",\
        "world",\
        "geo",\
        "li9",\
        "n17",\
        "fn",\
        ]

    radio = ["li9",\
    "n17",\
    ]
    return (components,other,signal_components,background_components,radio)